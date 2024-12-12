import re
import torch
from torch_geometric.data import Data

node_types = { #lets try this without containers.
    "Class": 0,
    "Function": 1,
    "If": 2,
    "For": 3,
    "While": 4,
    "VarDecl": 5,
    "Call": 6,
    "Statement": 7
}

def remove_comments(code):
    code = re.sub(r'//.*', '', code)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    return code

def starts_class_solution(line):
    # every leetcode cpp file has "class Solution" encompassing the code
    return "class Solution" in line

#function definition detection:
#matches something like:
# returnType functionName(...) {
func_def_regex = re.compile(r'^[A-Za-z_][A-Za-z0-9_:\[\]]*\s+[A-Za-z_][A-Za-z0-9_]*\s*\([^)]*\)\s*\{')

def is_function_def(line):
    return bool(func_def_regex.match(line.strip()))

def is_if(line):
    return re.match(r'^\s*if\s*\(', line) is not None

def is_for(line):
    return re.match(r'^\s*for\s*\(', line) is not None

def is_while(line):
    return re.match(r'^\s*while\s*\(', line) is not None

def is_var_decl(line):
    #checks if line has a type-like token and ends with ';'
    #can catch false positives!! 
    #this is absurdly difficult to correct.
    return re.match(r'^\s*[A-Za-z_][A-Za-z0-9_<>,]*\s+[A-Za-z_][A-Za-z0-9_]*\s*(=|;)', line) is not None

def is_call(line):
    #check for foo(...) not preceded by conditional/loop
    if any(kw in line for kw in ["if(", "for(", "while("]):
        return False
    return re.search(r'[A-Za-z_][A-Za-z0-9_]*\s*\(', line) is not None and ';' in line

def create_node(node_type):
    #node is a dict
    return {"type": node_type, "children": []}

def connect(parent, child):
    parent["children"].append(child)

def build_data_object(root):
    #tree -> nodes/edges
    #we'll do a DFS
    nodes = []
    edges = []  # parent->child
    sibling_edges = []
    
    def dfs(node, parent_idx=None):
        idx = len(nodes)
        nodes.append(node)
        #parent->child edges
        if parent_idx is not None:
            edges.append((parent_idx, idx))
        
        for i, ch in enumerate(node["children"]):
            ch_idx = dfs(ch, idx)
            #sibling edges
            if i > 0:
                # previous sibling is node["children"][i-1]
                prev_sib = nodes.index(node["children"][i-1])
                #actually, indexing nodes like this is O(n).
                #we can track indices as we go.
                #return child indices from dfs to avoid searching:
                #already done: ch_idx is child index, store previous child index
                prev_sib_idx = ch_idx - (len(ch["children"]) + 1) #messy, fix later.
                #should handle siblings differently:

        return idx

    #modified dfs that returns indices and also handle siblings cleanly
    nodes = []
    def dfs_refactored(node):
        idx = len(nodes)
        nodes.append(node)
        child_indices = []
        for ch in node["children"]:
            ch_idx = dfs_refactored(ch)
            child_indices.append(ch_idx)
        #have all children indices, add edges
        #parent->child
        for c in child_indices:
            edges.append((idx, c))
        #siblings.
        for i in range(len(child_indices)-1):
            #forward sibling
            sibling_edges.append((child_indices[i], child_indices[i+1]))
            sibling_edges.append((child_indices[i+1], child_indices[i]))
        return idx

    dfs_refactored(root)

    #node features
    x = []
    for node in nodes:
        vec = [0]*len(node_types)
        vec[node_types[node["type"]]] = 1
        x.append(vec)
    x = torch.tensor(x, dtype=torch.float)

    #combine edges
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

    #find class Solution
    solution_node = None
    inside_solution = False
    #stack for blocks
    #one main stack, top of which is the current parent node
    stack = []
    
    for i, raw_line in enumerate(lines):
        line = raw_line.strip()
        if not inside_solution and starts_class_solution(line):
            #find a { to confirm we are inside the class block
            if '{' in line:
                inside_solution = True
                solution_node = create_node("Class")
                stack = [solution_node]
            else:
                #maybe next line has '{'
                #set a flag and wait for '{'
                solution_node = create_node("Class")
                stack = [solution_node]
                inside_solution = True
            continue
        
        if not inside_solution:
            continue

        #inside class solution now
        #block starts and ends
        #a '}'  might close a function or a control structure
        if '}' in line:
            #pop from stack if not the root class
            if len(stack) > 1:
                stack.pop()
            continue

        #detect function definition
        if is_function_def(line):
            func_node = create_node("Function")
            connect(stack[-1], func_node)
            stack.append(func_node)
            continue

        #inside a function, look for control structures:
        if len(stack) > 1:  #means we are inside a function or deeper
            if is_if(line):
                if_node = create_node("If")
                connect(stack[-1], if_node)
                stack.append(if_node)
                #if there's an immediate '{' on the same line, stay inside this block
                #if no '{', we might expect the next line to have it
                if '{' not in line:
                    #treat it like a block that must end with '}'
                    pass
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

            #no recognized control structure:
            #variable declaration?
            if is_var_decl(line):
                var_node = create_node("VarDecl")
                connect(stack[-1], var_node)
                continue

            #function call?
            if is_call(line):
                call_node = create_node("Call")
                connect(stack[-1], call_node)
                continue

            #else, a statement
            if line and not line.startswith('}'):
                stmt_node = create_node("Statement")
                connect(stack[-1], stmt_node)
                continue

    if solution_node is None:
        #no class solution found, create a dummy
        #should NEVER TRIGGER.
        print("no solution_node found. what's wrong with the file champ?")
        solution_node = create_node("Class")

    data = build_data_object(solution_node)
    return data

data = parse_file("../dataset/1.cpp")
print(data)
print(data.x.shape, data.edge_index.shape)
