import glob

def read_small():

    files = glob.glob("small/*")

    graphs = dict()

    for each in files:
        with open(each, 'r', encoding="utf8") as f:

            name = f.readline()
            line = f.readline()
            data = line.split(" ")
            vertex = int(data[0])
            matrix = [[0]*vertex for _ in range(vertex)] 

            while line:
                line = f.readline()
                if(len(line)>1):
                    edges = line.split(" ")
                    f_v = int(edges[0])
                    s_v = int(edges[1].replace("\n", ""))
                    matrix[f_v - 1][s_v - 1] = 1
                    matrix[s_v - 1][f_v - 1] = 1


            graphs[name] = matrix
    return graphs

def read_harwell():
    files = glob.glob("harwellboeing/*")

    graphs = dict()
    for each in files:
        with open(each, 'r', encoding="utf8") as f:

            name = f.readline()
            line = f.readline()
            data = line.split(" ")
            vertex = int(data[0])
            matrix = [[0]*vertex for _ in range(vertex)] 

            while line:
                line = f.readline()
                if(len(line)>1):
                    edges = line.split(" ")
                    f_v = int(edges[0])
                    s_v = int(edges[1].replace("\n", ""))
                    matrix[f_v - 1][s_v - 1] = 1
                    matrix[s_v - 1][f_v - 1] = 1


            graphs[name] = matrix
    return graphs

def read_grids():

    files = glob.glob("grids/*")

    graphs = dict()

    for each in files:
        with open(each, 'r', encoding="utf8") as f:

            name = f.readline()
            line = f.readline()
            line = line.split(" ")
            s = len(line) - 1
            matrix = [[0]*s for _ in range(s)] 
            i = 0
            while line:
                j = 0
                line.pop()
                for item in line:
                    matrix[i][j] = int(item)
                    j += 1
                i+=1
                line = f.readline()
                if(len(line) < 1): 
                    break 
                line = line.split(" ")
            graphs[name] = matrix
    
    return graphs

def evaluate(matrix, solution):
    max_cut = 0
    cut = 0
    for i in range(len(solution)):
        for j in range(i):
            for k in range(i, len(solution)):
                if(matrix[solution[j]][solution[k]] == 1 and j != k):
                    cut += 1
        if(cut > max_cut):
            max_cut = cut
        cut = 0
    return max_cut

def evaluate_dict(graphs):
    val_solutions = dict()
    for graph in graphs:
        solution =  [i for i in range(len(graphs[graph][0]))]
        val_solutions[graph] = evaluate(graphs[graph], solution)
    return val_solutions

def main():
    
    small = read_small()
    # harwell = read_harwell()
    grid = read_grids()
    print(evaluate_dict(small))
    # print(evaluate_dict(harwell))
    print(evaluate_dict(grid))
    

if __name__ == "__main__":
    main()