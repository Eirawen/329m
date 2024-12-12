import torch
import torch.nn as nn
from torch_geometric.nn import GATConv, global_mean_pool

class GATNet(nn.Module):
    def __init__(self, in_channels, hidden_channels, out_channels=1, heads=2, dropout=0.2, task='classification'): #do make sure we don't accidentally use the default task
        super(GATNet, self).__init__()
        self.task = task
        self.conv1 = GATConv(in_channels, hidden_channels, heads=heads, dropout=dropout)
        self.conv2 = GATConv(hidden_channels * heads, hidden_channels, heads=1, concat=False, dropout=dropout)
        self.lin = nn.Linear(hidden_channels, out_channels)
        
    def forward(self, x, edge_index, batch):
        x = self.conv1(x, edge_index)
        x = torch.relu(x)
        x = self.conv2(x, edge_index)
        x = torch.relu(x)
        
        x = global_mean_pool(x, batch)
        x = self.lin(x)
        #classification, x is [batch_size, num_classes]
        #regression, x is [batch_size, 1]
        return x
