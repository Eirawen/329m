# train.py
import torch
import torch.nn as nn
import torch.optim as optim
from torch_geometric.loader import DataLoader
from models.gat_model import GATNet
from utils.data_loading import read_labels, split_data_by_problem, create_dataset, CodeRuntimeDataset

def main():
    modelTestIncrement = 0
    csv_path = 'dataset/labels.csv'
    data = read_labels(csv_path)

    #data by problem
    train_data, test_data = split_data_by_problem(data, train_ratio=0.8)

    #classification or regression
    #task = 'classification'
    task = 'regression'
    model_name = "model_ir_containers_regression" #change per IR.  
    train_list = create_dataset(train_data, task=task)
    test_list = create_dataset(test_data, task=task)

    train_dataset = CodeRuntimeDataset(root='.', data_list=train_list, task=task)
    test_dataset = CodeRuntimeDataset(root='.', data_list=test_list, task=task)

    train_loader = DataLoader(train_dataset, batch_size=8, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=8, shuffle=False)

    if task == 'classification':
        out_channels = 5
    else:
        #regression: single output
        out_channels = 1

    #we have 9 types total with containers, 8 types without.
    in_channels = 9  
    hidden_channels = 32

    model = GATNet(in_channels, hidden_channels, out_channels=out_channels, task=task)
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    model = model.to(device)

    if task == 'classification':
        criterion = nn.CrossEntropyLoss()
    else:
        criterion = nn.MSELoss()

    #hyperparameter tuning handled elsewhere. 
    optimizer = optim.Adam(model.parameters(), lr=0.001)

    epochs = 1000 
    best_metric = None
    for epoch in range(1, epochs+1):
        # Train
        model.train()
        total_loss = 0
        for batch in train_loader:
            batch = batch.to(device)
            optimizer.zero_grad()
            out = model(batch.x, batch.edge_index, batch.batch)
            loss = criterion(out, batch.y)
            loss.backward()
            optimizer.step()
            total_loss += loss.item()
        avg_loss = total_loss / len(train_loader)

        model.eval()
        if task == 'classification':
            correct = 0
            total = 0
            with torch.no_grad():
                for batch in test_loader:
                    batch = batch.to(device)
                    out = model(batch.x, batch.edge_index, batch.batch)
                    pred = out.argmax(dim=1)
                    correct += (pred == batch.y).sum().item()
                    total += batch.y.size(0)
            val_acc = correct / total if total > 0 else 0
            print(f"Epoch {epoch}, Loss: {avg_loss:.4f}, Val Acc: {val_acc:.4f}")
        else:
            #regrets-ion.
            mse_sum = 0
            count = 0
            with torch.no_grad():
                for batch in test_loader:
                    batch = batch.to(device)
                    out = model(batch.x, batch.edge_index, batch.batch)
                    mse_sum += ((out - batch.y)**2).sum().item()
                    count += batch.y.size(0)
            val_mse = mse_sum / count if count > 0 else 0
            print(f"Epoch {epoch}, Loss: {avg_loss:.4f}, Val MSE: {val_mse:.4f}")
    torch.save(model.state_dict(), f"{model_name}_{modelTestIncrement}.pth")

if __name__ == "__main__":
    main()
