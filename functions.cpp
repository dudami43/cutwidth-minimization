#include <bits/stdc++.h>
#include "functions.h"

int evaluate(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& solution)
{
    int max_cut = 0;
    int cut = 0;
    int count_max = 0;
    for (int i = 0; i < solution.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            for (int k = i; k < solution.size(); k++)
            {
                if (adj_matrix[solution[j]][solution[k]] == 1 and j != k)
                {
                    cut += 1;
                }
            }
        }
        if (cut >= max_cut)
        {
            max_cut = cut;
            count_max++;
        }
        cut = 0;
        //Novas funções de avaliação:
        //--Multiplicar o max_cut pelo número de vezes que ele aparece
        //--Média dos cortes
    }
    return max_cut;
}

int cutwidth(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& solution)
{
    int max_cut = 0;
    int cut = 0;
    for (int i = 0; i < solution.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            for (int k = i; k < solution.size(); k++)
            {
                if (adj_matrix[solution[j]][solution[k]] == 1 and j != k)
                {
                    cut += 1;
                }
            }
        }
        if (cut >= max_cut)
        {
            max_cut = cut;
        }
        cut = 0;
    }
    return max_cut;
}

std::vector<std::vector<int>> genNeighbourhood(std::vector<int>& initial_solution)
{
    std::vector<std::vector<int>> neighbours(initial_solution.size());
    std::vector<int> aux(initial_solution.size());
    int num_aux;
    for(int i = 0; i < initial_solution.size(); i++) //Vetor de vizinhos
    {
        for(int j = 0; j < initial_solution.size(); j++) //Vetor auxiliar
        {
            aux[j] = initial_solution[j];
            if(j == i && j < initial_solution.size() - 1)
            {
                aux[j+1] = initial_solution[j];
                aux[j] = initial_solution[j+1];
                j++;
            }
        }
        if(i == initial_solution.size() - 1)
        {
            aux[initial_solution.size() - 1] = initial_solution[0];
            aux[0] = initial_solution[initial_solution.size() - 1];
        }
        neighbours[i] = aux;
    }
    /*for(int i = 0; i < initial_solution.size(); i++) //Vetor de vizinhos
    {
        for(int j = 0; j < initial_solution.size(); j++) //Vetor auxiliar
        {
            std::cout << neighbours[i][j] << " ";
        }
        std::cout << "\n";
    }*/
    return neighbours;
}

int local_search(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& initial_solution)
{
    bool is_changing = false;
    std::vector<int> best_solution = initial_solution; 
    int best_value = evaluate(adj_matrix, initial_solution);
    std::cout << " " << best_value << " ";
    do
    {
        std::vector<std::vector<int>> neighbours = genNeighbourhood(best_solution);
        int current_value;
        is_changing = false;
        for(int i = 0; i < neighbours.size(); i++)
        {                       
            current_value = evaluate(adj_matrix, neighbours[i]);
            /*for(int j = 0; j < neighbours[i].size(); j++)
            {
                std::cout << neighbours[i][j] << " ";
            }
            std::cout << std::endl << "cur_val " << current_value << std::endl;*/
            if(current_value < best_value)
            {
                best_solution = neighbours[i];
                best_value = current_value;
                is_changing = true;
            }
        }
    }while(is_changing);
    return best_value;
}