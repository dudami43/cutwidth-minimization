#include <bits/stdc++.h>
#include "functions.h"
#include "parser.h"
//g++ -std=c++11 main.cpp parser.cpp functions.cpp
int main()
{
    
    std::ifstream file;
    std::string filename;
    file.open("all_files");

    if (file.is_open())
    {
        while (getline(file, filename))
        {
            std::vector<std::vector<int>> adj_matrix;
            std::cout << filename << " ";
            try
            {
                adj_matrix = get_adj_matrix(filename);
                std::vector<int> initial_solution;
                for( int i = 0; i < adj_matrix.size(); i++ )
                {
                    initial_solution.push_back( i );
                }
                std::cout << local_search(adj_matrix, initial_solution) << std::endl;
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