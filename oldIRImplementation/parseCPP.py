import re
import sys
import networkx as nx
import matplotlib.pyplot as plt

#this absolutely sucks. I'll keep it here for history purposes but oh my god Khaled, on your deathbed
#you're going to be like "i wish i had more time" and you'll HAVE SPENT HOURS ON THIS MONSTROSITY.

def extract_function_name(line):
    match = re.match(r"\w+\s+(\w+)\s*\(.*?\)\s*\{", line)
    return match.group(1) if match else "no clue"

def parse_cpp(file_path):
    with open(file_path, 'r') as file:
        file_content = file.readlines()

    functions = []
    current_function = None
    scope_stack = []

    for line in file_content:
        line = line.strip()
        if re.match(r"\w+\s+\w+\s*\(.*?\)\s*\{", line): #func declaration regex
            if current_function:
                functions.append(current_function)
            current_function = {
                "name": extract_function_name(line),
                "loop_count": 0,
                "max_loop_depth": 0,
                "statement_count": 0,
                "if_count": 0,
                "array_use": 0,
                "pointer_use": 0,
                "template_use": 0,
                "current_depth": 0,
                "vector_use": 0,
                "map_use": 0,
                "set_use": 0,
                "string_use": 0
            }
        if current_function is None:
            continue
        #scope depth
        if '{' in line:
            scope_stack.append("{")
            current_function["current_depth"] += 1
            current_function["max_loop_depth"] = max(
                current_function["max_loop_depth"], current_function["current_depth"]
            )
        if '}' in line and scope_stack:
            scope_stack.pop()
            current_function["current_depth"] -= 1

        #loops, branches.
        if any(keyword in line for keyword in ["for", "while"]):
            current_function["loop_count"] += 1
        if "if" in line:
            current_function["if_count"] += 1

        current_function["statement_count"] += line.count(';')

        #arrays, pointers, templates
        if re.search(r"\w+\s+\w+\[.*?\];", line):
            current_function["array_use"] += 1
        if re.search(r"\w+\s+\*.*?;", line):
            current_function["pointer_use"] += 1
        if "template" in line:
            current_function["template_use"] += 1
        if "std::vector" in or "vector" line:
            current_function["vector_use"] += 1
        if "std::map" or "map" in line:
            current_function["map_use"] += 1
        if "std::set" or "set" in line:
            current_function["set_use"] += 1
        if "std::string" or "string" in line:
            current_function["string_use"] += 1


    #save last function
    if current_function:
        functions.append(current_function)

    return functions

def plot_ir_graph(functions, output_file="ir_graph.png"):
    G = nx.DiGraph()

    for i, func in enumerate(functions):
        G.add_node(func["name"], **{
            "Loops": func["loop_count"],
            "Max Loop Depth": func["max_loop_depth"],
            "Statements": func["statement_count"],
            "Conditionals": func["if_count"],
            "Array Uses": func["array_use"],
            "Pointer Uses": func["pointer_use"],
            "Template Uses": func["template_use"],
            "Vector Uses": func["vector_use"],
            "Map Uses": func["map_use"],
            "Set Uses": func["set_use"],
            "String Uses": func["string_use"]
        })
        if i > 0:  
            G.add_edge("main", func["name"])

    pos = nx.spring_layout(G)
    nx.draw_networkx_nodes(G, pos, node_size=2000, node_color="lightblue")
    nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
    nx.draw_networkx_edges(G, pos, arrowstyle="->", arrowsize=20)

    for node, data in G.nodes(data=True):
        attr_text = "\n".join(f"{k}: {v}" for k, v in data.items())
        x, y = pos[node]
        plt.text(x, y - 0.1, attr_text, fontsize=8, ha="center", bbox=dict(facecolor="white", alpha=0.8))

    plt.title("Control Flow Graph with IR Features")
    plt.axis("off")
    plt.show()
    plt.show(block=True)
    plt.savefig(output_file, format="png", dpi=300)



def main():
    if len(sys.argv) != 2:
        print("make sure its python parse_cpp.py <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    if not (file_path.endswith(".c") or file_path.endswith(".cpp")):
        print("hey goof it must be a .c or .cpp file")
        sys.exit(1)

    functions = parse_cpp(file_path)
    cpp = False 
    if file_path.endswith(".cpp"):
        cpp = True

    for func in functions:
        print(f"Function Name: {func['name']}")
        print(f"  Loops: {func['loop_count']}")
        print(f"  Max Loop Depth: {func['max_loop_depth']}")
        print(f"  Statements: {func['statement_count']}")
        print(f"  Conditionals (if): {func['if_count']}")
        print(f"  Array Uses: {func['array_use']}")
        print(f"  Pointer Uses: {func['pointer_use']}")
        print(f"  Template Uses: {func['template_use']}")
        if cpp:
            print(f"  Vector Uses: {func['vector_use']}")
            print(f"  Map Uses: {func['map_use']}")
            print(f"  Set Uses: {func['set_use']}")
            print(f"  String Uses: {func['string_use']}")
        print("-" * 40)

    plot_ir_graph(functions)
    print('is matplotlib working yet')



if __name__ == "__main__":
    main()
