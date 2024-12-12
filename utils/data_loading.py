# utils/data_loading.py
import os
import csv
import torch
import random 
from collections import defaultdict
from torch_geometric.data import InMemoryDataset
from utils.graph_parsing_containers import parse_file

def read_labels(csv_path):
    #file_number, runtime_ms, problem_name
    data = []
    with open(csv_path, 'r') as f:
        reader = csv.reader(f)
        next(reader) #skip headers
        for row in reader:
            file_num = row[0].strip()
            runtime = float(row[1].strip())
            problem = row[2].strip()
            data.append((file_num, runtime, problem))
    return data

def bin_runtime(runtime, bins=[0, 10, 30, 70]): #modified for the reduced hard dataset.
    for i, b in enumerate(bins):
        if runtime <= b:
            return i
    return len(bins)

def split_data_by_problem(data, train_ratio=0.8):

    problem_dict = defaultdict(list)
    for d in data:
        problem_dict[d[2]].append(d)
    
    train_data = []
    test_data = []
    for problem, items in problem_dict.items():
        #test if shuffling changes performance.
        #random.shuffle(items)
        split_idx = int(len(items)*train_ratio)
        train_data.extend(items[:split_idx])
        test_data.extend(items[split_idx:])
    return train_data, test_data

class CodeRuntimeDataset(InMemoryDataset):
    def __init__(self, root, data_list, task='classification', transform=None, pre_transform=None):
        self.task = task
        self.data_list = data_list
        super(CodeRuntimeDataset, self).__init__(root, transform, pre_transform)
        self.data, self.slices = self.collate(self.data_list)

    @property
    def processed_file_names(self):
        return []

    def process(self):
        pass

def create_dataset(data, code_root='./dataset/', task='classification'):
    data_list = []
    for (file_num, runtime, problem) in data:
        filepath = os.path.join(code_root, f"{file_num}.cpp")
        if not os.path.exists(filepath):
            continue
        graph_data = parse_file(filepath)
        if task == 'classification':
            y = torch.tensor([bin_runtime(runtime)], dtype=torch.long)
        else:
            #regression: predict runtime directly
            #optionally normalize runtime by dividing by max runtime
            #keep it raw for now.
            y = torch.tensor([runtime], dtype=torch.float)
        graph_data.y = y
        data_list.append(graph_data)
    return data_list
