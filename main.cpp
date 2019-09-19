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

                int init_value = evaluate(adj_list, initial_solution);
                int past_init_value = evaluate(adj_list, past_initial_solution);

                std::pair<int, std::vector<int> > init_value_list = max_cutwidth_list(adj_list, initial_solution);
                std::pair<int, std::vector<int> > past_init_value_list = max_cutwidth_list(adj_list, past_initial_solution);
                
                std::cout << "solucao inicial nova: " << init_value << "\n";
                //std::cout << best_simulated_annealing(adj_list, initial_solution);
                //std::cout << iterated_local_search(adj_list, initial_solution, "ms", 100);
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
