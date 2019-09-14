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
                std::vector<int> past_initial_solution;
                for(int i=0 ; i<adj_list.size(); i++){
                    past_initial_solution.push_back(i);
                }

                int init_value = evaluate(adj_matrix, initial_solution);
                int past_init_value = evaluate(adj_matrix, past_initial_solution);

                std::pair<int, std::vector<int> > init_value_list = max_cutwidth_list(adj_list, initial_solution);
                std::pair<int, std::vector<int> > past_init_value_list = max_cutwidth_list(adj_list, past_initial_solution);
                
                bool result = testa_reevaluate(adj_list, initial_solution);
                if(result){
                    std::cout << "OK!" << std::endl;
                }else{
                    std::cout << "Nao OK :(" << std::endl; 
                }

                // std::cout << "solucao inicial antiga: " << past_init_value << std::endl;
                std::cout << "solucao inicial nova: " << init_value << "\n";
                // std::cout << "best improvement \n";
                // std::cout << "vizinhanca adjacente: " << local_search(adj_matrix, initial_solution, "a", "best") << "\n";
                // std::cout << "vizinhanca nao adjacente: " << local_search(adj_matrix, initial_solution, "noAdj", "best") << std::endl;
                // std::cout << "move and swap: " << local_search(adj_matrix, initial_solution, "ms", "best") << std::endl;
                // std::cout << "simulated annealing\n";
                // std::cout << "vizinhanca nao adjacente: " << simulated_annealing(adj_matrix, initial_solution, 10, 1, 0.95, false) << std::endl;
                // std::cout << "move and swap: " << simulated_annealing(adj_matrix, initial_solution, 5, 1, 0.7, true) << std::endl;
                std::cout << "noAdj: " << iterated_local_search(adj_matrix, initial_solution, "noAdj") << std::endl;
                std::cout << "ms: " << iterated_local_search(adj_matrix, initial_solution, "ms") << std::endl;
                std::cout << std::endl;

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
