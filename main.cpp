#include <bits/stdc++.h>
#include "functions.h"
#include "parser.h"
//g++ -std=c++11 main.cpp parser.cpp functions.cpp
int main(int argc, char *argv[])
{
    srand (time(NULL));

    char *file_name = new char[500];
    strcpy(file_name, "files/");
    if(argc == 1)
        strcat(file_name, "pvanet_files");
    else
        strcat(file_name, argv[1]);

    std::ifstream file;
    std::string filename;
    file.open(file_name);

    delete file_name;

    int improvements[100][100];
    for(int i = 0; i <100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            improvements[i][j] = 0;
        }
    }


    if (file.is_open())
    {
        while (getline(file, filename))
        {
            std::vector<std::vector<int>> adj_matrix, adj_list;
            std::cout << filename << ":\n";
            try
            {
                adj_matrix = get_adj_matrix(filename);
                adj_list = get_adj_list(adj_matrix);

                std::vector<int> initial_solution = first_solution(adj_list);
                
                int init_value = evaluate(adj_list, initial_solution);

                std::pair<int, std::vector<int> > init_value_list = max_cutwidth_list(adj_list, initial_solution);

                std::cout << "SA: " << simulated_annealing(adj_list, initial_solution).first << std::endl;
                std::cout << "ILS: " << smart_iterated_local_search(adj_list, initial_solution) << std::endl;
                std::cout << "GRASP: " << grasp(adj_list) << std::endl;

                // Funcao que roda o algoritmo 10 vezes e imprime o resultado e o tempo de cada iteracao
                //best_solution(adj_list, initial_solution, "sa");
                //best_solution(adj_list, initial_solution, "sils");
                //best_solution(adj_list, initial_solution, "grasp");

            }
            catch (char const *param)
            {
                std::cout << param << std::endl;
                return 0;
            }
            
        }
        file.close();
    }
    else
    {
        throw "Unable to open the file";
    }
    return 0;
}
