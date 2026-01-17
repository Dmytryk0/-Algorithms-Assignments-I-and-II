import subprocess
import matplotlib.pyplot as plt
import os

PROGRAMS = {
    "sorting": "assignment1/task1/task_a/sorter",
    "olsen": "assignment1/task1/task_b/olsen",
    "vector": "assignment1/task2/vector_test",
    "pivots": "assignment1/task3/pivots",
    "bst": "assignment2/task1/bst_test"
}

def run_cpp(path):
    if not os.path.exists(path):
        if "bst_test" in path and os.path.exists("assignment2/task2/bst_test"):
            path = "assignment2/task2/bst_test"
        else:
            return ""
    try:
        return subprocess.run([path], capture_output=True, text=True).stdout
    except:
        return ""

def plot_lines(output, filename, title, ylabel="Time (s)"):
    data = {}
    for line in output.splitlines():
        if "," in line and "Algorithm" not in line:
            parts = line.split(",")
            if len(parts) == 3:
                name, size, time = parts[0], int(parts[1]), float(parts[2])
                if name not in data: data[name] = []
                data[name].append((size, time))
    
    if not data: return
    plt.figure(figsize=(10, 6))
    for name, points in data.items():
        points.sort()
        plt.plot([p[0] for p in points], [p[1] for p in points], marker='o', label=name)
    plt.title(title); plt.xlabel("Input Size (N)"); plt.ylabel(ylabel)
    plt.legend(); plt.grid(True)
    plt.savefig(filename); plt.close()
    print(f"Generated {filename}")

def plot_bars(output, filename, title):
    names, times = [], []
    for line in output.splitlines():
        parts = line.split(',') if ',' in line else line.split()
        if len(parts) >= 2 and "Container" not in parts[0] and "Operation" not in parts[0]:
            try:
                names.append(parts[0].strip()); times.append(float(parts[1]))
            except: pass
    if not names: return
    plt.figure(figsize=(10, 6)); plt.bar(names, times, color=['skyblue', 'salmon', 'lightgreen'])
    plt.title(title); plt.ylabel("Time (s)"); plt.grid(axis='y')
    plt.savefig(filename); plt.close()
    print(f"Generated {filename}")

def main():
    plot_lines(run_cpp(PROGRAMS["sorting"]), "graph_sorting.png", "Sorting Algorithms")
    plot_lines(run_cpp(PROGRAMS["olsen"]), "graph_olsen.png", "Radix vs Quick Sort")
    plot_bars(run_cpp(PROGRAMS["vector"]), "graph_vector.png", "Vector vs List Append")
    plot_lines(run_cpp(PROGRAMS["pivots"]), "graph_pivots.png", "1-Pivot vs 2-Pivot QuickSort") 
    plot_bars(run_cpp(PROGRAMS["bst"]), "graph_trees.png", "BST Operations")

if __name__ == "__main__":
    main()