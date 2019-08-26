#include <bits/stdc++.h>
#include "functions.h"
#include "parser.h"
//g++ -std=c++11 main.cpp parser.cpp functions.cpp
int main()
{
    
    std::ifstream file;
    std::string filename;
    file.open("files/pvanet_files");

    if (file.is_open())
    {
        while (getline(file, filename))
        {
            std::vector<std::vector<int>> adj_matrix;
            std::cout << filename << ":" << std::endl;
            try
            {
                adj_matrix = get_adj_matrix(filename);
                std::vector<int> initial_solution;
                for( int i = 0; i < adj_matrix.size(); i++ )
                {
                    initial_solution.push_back( i );
                }
                int init_value = evaluate(adj_matrix, initial_solution);
                std::cout << "best improviment - ";
                std::cout << "solucao inicial: " << init_value << " - ";
                //std::cout << "vizinhanca adjacente: " << local_search(adj_matrix, initial_solution, "a", "best") << " - ";
                std::cout << "vizinhanca nao adjacente: " << local_search(adj_matrix, initial_solution, "noAdj", "best", 1) << std::endl;

                /*std::cout << "first improviment - ";
                std::cout << "solucao inicial: " << init_value << " - ";
                std::cout << "vizinhanca adjacente: " << local_search(adj_matrix, initial_solution, "adj", "first") << " - ";
                std::cout << "vizinhanca nao adjacente: " << local_search(adj_matrix, initial_solution, "noAdj", "first") << std::endl;

                std::cout << "random selection - ";
                std::cout << "solucao inicial: " << init_value << " - ";
                std::cout << "vizinhanca adjacente: " << local_search(adj_matrix, initial_solution, "adj", "random") << " - ";
                std::cout << "vizinhanca nao adjacente: " << local_search(adj_matrix, initial_solution, "noAdj", "random") << std::endl;
                */
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