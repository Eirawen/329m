import re
import torch
from torch_geometric.data import Data
import networkx as nx
import matplotlib.pyplot as plt

#add ContainerDecl node type
node_types = {
    "Class": 0,
    "Function": 1,
    "If": 2,
    "For": 3,
    "While": 4,
    "VarDecl": 5,
    "Call": 6,
    "Statement": 7,
    "ContainerDecl": 8
}

def remove_comments(code):
    code = re.sub(r'//.*', '', code)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    return code

def starts_class_solution(line):
    return "class Solution" in line

func_def_regex = re.compile(r'^[A-Za-z_][A-Za-z0-9_:\[\]]*\s+[A-Za-z_][A-Za-z0-9_]*\s*\([^)]*\)\s*\{')

def is_function_def(line):
    return bool(func_def_regex.match(line.strip()))

def is_if(line):
    return re.match(r'^\s*if\s*\(', line) is not None

def is_for(line):
    return re.match(r'^\s*for\s*\(', line) is not None

def is_while(line):
    return re.match(r'^\s*while\s*\(', line) is not None

def is_container_decl(line):
    #std::vector<, std::stack<, std::queue< lines.
    #pattern: std::(vector|stack|queue)<...> varname ...;
    #std::(vector|stack|queue)<.*>\s+\w+\s*(=|;)
    container_pattern = r'^\s*std::(vector|stack|queue)<[^>]+>\s+[A-Za-z_][A-Za-z0-9_]*\s*(=|;|$)'
    return bool(re.match(container_pattern, line.strip()))

def is_var_decl(line):
    #ontainer decl, handle separately
    if is_container_decl(line):
        return False  
    return re.match(r'^\s*[A-Za-z_][A-Za-z0-9_<>,]*\s+[A-Za-z_][A-Za-z0-9_]*\s*(=|;)', line) is not None

def is_call(line):
    if any(kw in line for kw in ["if(", "for(", "while("]):
        return False
    return re.search(r'[A-Za-z_][A-Za-z0-9_]*\s*\(', line) is not None and ';' in line

def create_node(node_type):
    return {"type": node_type, "children": []}

def connect(parent, child):
    parent["children"].append(child)

def build_data_object(root):
    nodes = []
    edges = []
    sibling_edges = []

    def dfs_refactored(node):
        idx = len(nodes)
        nodes.append(node)
        child_indices = []
        for ch in node["children"]:
            ch_idx = dfs_refactored(ch)
            child_indices.append(ch_idx)
        for c in child_indices:
            edges.append((idx, c))
        for i in range(len(child_indices)-1):
            sibling_edges.append((child_indices[i], child_indices[i+1]))
            sibling_edges.append((child_indices[i+1], child_indices[i]))
        return idx

    dfs_refactored(root)

    x = []
    for node in nodes:
        vec = [0]*len(node_types)
        vec[node_types[node["type"]]] = 1
        x.append(vec)
    x = torch.tensor(x, dtype=torch.float)

    all_edges = edges + sibling_edges
    if len(all_edges) > 0:
        edge_index = torch.tensor(all_edges, dtype=torch.long).t().contiguous()
    else:
        edge_index = torch.empty((2,0), dtype=torch.long)

    data = Data(x=x, edge_index=edge_index)
    return data

def parse_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        code = f.read()
    code = remove_comments(code)
    lines = code.split('\n')

    solution_node = None
    inside_solution = False
    stack = []

    for i, raw_line in enumerate(lines):
        line = raw_line.strip()
        if not inside_solution and starts_class_solution(line):
            if '{' in line:
                inside_solution = True
                solution_node = create_node("Class")
                stack = [solution_node]
            else:
                inside_solution = True
                solution_node = create_node("Class")
                stack = [solution_node]
            continue

        if not inside_solution:
            continue

        if '}' in line:
            if len(stack) > 1:
                stack.pop()
            continue

        if is_function_def(line):
            func_node = create_node("Function")
            connect(stack[-1], func_node)
            stack.append(func_node)
            continue

        if len(stack) > 1:
            if is_if(line):
                if_node = create_node("If")
                connect(stack[-1], if_node)
                stack.append(if_node)
                continue

            if is_for(line):
                for_node = create_node("For")
                connect(stack[-1], for_node)
                stack.append(for_node)
                continue

            if is_while(line):
                while_node = create_node("While")
                connect(stack[-1], while_node)
                stack.append(while_node)
                continue

            if is_container_decl(line):
                container_node = create_node("ContainerDecl")
                connect(stack[-1], container_node)
                continue

            if is_var_decl(line):
                var_node = create_node("VarDecl")
                connect(stack[-1], var_node)
                continue

            if is_call(line):
                call_node = create_node("Call")
                connect(stack[-1], call_node)
                continue

            if line and not line.startswith('}'):
                stmt_node = create_node("Statement")
                connect(stack[-1], stmt_node)
                continue

    if solution_node is None:
        solution_node = create_node("Class")

    data = build_data_object(solution_node)
    return data


#visualize it for report.
def visualize_graph(data, node_type_map=node_types):
    edge_index = data.edge_index.cpu().numpy()
    G = nx.Graph()
    for i in range(data.x.shape[0]):
        node_type_idx = data.x[i].argmax().item()
        node_type = list(node_type_map.keys())[list(node_type_map.values()).index(node_type_idx)]
        G.add_node(i, type=node_type)

    for i in range(edge_index.shape[1]):
        src = edge_index[0, i]
        dst = edge_index[1, i]
        G.add_edge(src, dst)

    pos = nx.spring_layout(G, k=0.5, iterations=50)  #adjust k for spacing

    type_to_color = {
        "Class": "red",
        "Function": "orange",
        "If": "green",
        "For": "blue",
        "While": "purple",
        "VarDecl": "cyan",
        "Call": "yellow",
        "Statement": "gray",
        "ContainerDecl": "pink"
    }

    node_colors = []
    labels = {}
    for n, d in G.nodes(data=True):
        node_colors.append(type_to_color.get(d['type'], 'black'))
        labels[n] = d['type']

    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, node_color=node_colors, with_labels=False, node_size=500, alpha=0.9, font_size=8)
    nx.draw_networkx_labels(G, pos, labels=labels, font_size=7, font_color='black')

    plt.title("Code Graph Visualization")
    plt.axis('off')
    plt.tight_layout()
    plt.savefig('containersVisualization.png')
    plt.show()