#include <bits/stdc++.h>
#include "functions.h"

/**
 * Funcao de avaliacao
**/ 
int evaluate(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution, std::string metodo)
{
    if(metodo.compare("max") == 0) // Retorna o corte que afeta o maior numero de arestas (max_cutwidth)
        return max_cutwidth(adj_matrix, solution);
    else if(metodo.compare("n_max") == 0) // Retorna o corte maximo multiplicado pela sua ocorrencia (n_max_cutwidth)
        return n_max_cutwidth(adj_matrix, solution);
    else if(metodo.compare("mean") == 0) // Retorna a media dos cortes (mean_cutwidth)
        return mean_cutwidth(adj_matrix, solution);
}

/**
 * Metrica para avaliar uma dada solucao
 * Avaliacao: eh retornado o corte com maior numero de arestas
**/
int max_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution)
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

/**
 * Metrica para avaliar uma dada solucao
 * Avaliacao: eh retornado a media de todos os cortes
**/
int mean_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution)
{
    int max_cut = 0;
    int cut = 0;
    int cut_sum = 0;
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
        cut_sum += cut;
        cut = 0;
    }
    return cut_sum/solution.size();
}

/**
 * Metrica para avaliar uma dada solucao
 * Avaliacao: eh retornado o corte com maior numero de arestas, multiplicado pelo
 * numero de vezes que ele acontece
**/
int n_max_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution)
{
    int max_cut = 0;
    int cut = 0;
    int n_max_cut = 0;
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
        if (cut > max_cut)
        {
            max_cut = cut;
            n_max_cut = 1;
        }
        else if(cut == max_cut)
        {
            n_max_cut++;
        }
        cut = 0;
    }
    return n_max_cut*max_cut;
}

/**
 * Retorna todos os vizinhos de uma dada solucao
 * Vizinho: grafo onde dois vertices adjacentes da solucao inicial
 * estao com posicoes trocadas
**/
std::vector<std::vector<int>> genNeighbourhood(std::vector<int>& initial_solution)
{
    std::vector<std::vector<int>> neighbours(initial_solution.size());
    std::vector<int> aux(initial_solution.size());

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

/**
 * Retorna todos os vizinhos de uma dada solucao
 * Vizinho: grafo onde dois vertices quaisquer da solucao inicial
 * estao com posicoes trocadas
**/
std::vector<std::vector<int>> genNeighbourhood_noAdj(std::vector<int>& initial_solution, int limite_vertices)
{
    // Caso o numero de vertices no problema seja maior que o limite passado, adquire somente
    // o numero do limite de vizinhos
    std::vector<std::vector<int>> neighbours;
    if(initial_solution.size() > limite_vertices)
    {
        // Seta numero de vizinhos
        int num_vizinhos = 500;

        // Inicializa variaveis
        std::vector<std::pair<int, int>> usados;
        int init, end;
        std::pair<int, int> trade, trade_inv;

        // Reserva espaco para o vector de vizinhos
        neighbours.reserve(num_vizinhos);
        neighbours.reserve(2*num_vizinhos);

        int i=0;
        while(i < num_vizinhos)
        {    
            //std::cout << "Vizinho " << i << std::endl;
            // Adquire dois numeros aleatorios para representarem os vertices que trocarao de lugar
            init = abs(rand() % initial_solution.size());
            end = abs(rand() % initial_solution.size());
            //std::cout << i << " " << init << " " << end << std::endl;
            // Cria par de troca e o inverso do mesmo
            trade = std::make_pair(init, end);
            trade_inv = std::make_pair(end, init);
            auto pos = find(usados.begin(), usados.end(), trade);
            if(pos == usados.end())
            {
                std::vector<int> aux(initial_solution);
                int aux_swap = aux[init];
                aux[init] = aux[end];
                aux[end] = aux_swap;
                neighbours.push_back(aux); // Adiciona vizinho na vizinhanca
                usados.push_back(trade); // Adiciona tupla de valores como ja utilizados
                usados.push_back(trade_inv);
                i++;
            }
        }
    }
    else
    {
        neighbours.reserve(5040);

        for(int i = 0; i < initial_solution.size(); i++) //Vetor de vizinhos
        {
            for(int j = i+1; j < initial_solution.size(); j++) //Vetor auxiliar
            {
                std::vector<int> aux(initial_solution);
                int aux_swap = aux[i];
                aux[i] = aux[j];
                aux[j] = aux_swap;

                neighbours.push_back(aux);
            }
        }
    }
    return neighbours;
}

/**
 * Retorna o vizinho que tem a melhor solucao
 * Caso nenhum vizinho tenha solucao melhor que a atual, retorna -1
**/
std::pair<int, std::vector<int> > local_search_best_improvement(std::vector<std::vector<int> >& adj_matrix, std::vector<std::vector<int> >& neighbours, int best_value)
{
    std::vector<int> best_solution; 
    int current_value, initial_value = best_value;
    for(int i = 0; i < neighbours.size(); i++)
    {
        current_value = evaluate(adj_matrix, neighbours[i]);
        if(current_value < best_value)
        {
            best_solution = neighbours[i];
            best_value = current_value;
        }
    }
    if(best_value == initial_value)
    {
        std::vector<int> vazio;
        return std::make_pair(-1, vazio);
    }
    return std::make_pair(best_value, best_solution);
}

/**
 * Retorna o primeiro vizinho que tem solucao melhor que a atual
 * Caso nenhum vizinho tenha solucao melhor que a atual, retorna -1
**/
std::pair<int, std::vector<int> > local_search_first_improvement(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, int best_value)
{
    std::vector<int> best_solution; 
    int init = abs(rand() % initial_solution.size());
    int end = abs(rand() % initial_solution.size());
    int current_value, initial_value = best_value;
    for(int i = 0; i < neighbours.size(); i++)
    {
        current_value = evaluate(adj_matrix, neighbours[i]);
        if(current_value < best_value)
        {
            best_solution = neighbours[i];
            best_value = current_value;
        }
    }
    if(best_value == initial_value)
    {
        std::vector<int> vazio;
        return std::make_pair(-1, vazio);
    }
    return std::make_pair(best_value, best_solution);
}

/**
 * Retorna um vizinho aleatorio
**/
std::pair<int, std::vector<int> >  local_search_random_selection(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, int best_value)
{
    // Inicializa variaveis
    int init, end;

    // Adquire dois numeros aleatorios para representarem os vertices que trocarao de lugar
    init = abs(rand() % initial_solution.size());
    end = abs(rand() % initial_solution.size());
    
    // Gera swap aleatorio
    std::vector<int> rand_solution(initial_solution);
    int rand_solution_swap = rand_solution[init];
    rand_solution[init] = rand_solution[end];
    rand_solution[end] = rand_solution_swap;

    // Avalia a solucao adquirida
    int rand_value = evaluate(adj_matrix, rand_solution);

    if(best_value == rand_value)
    {
        std::vector<int> vazio;
        return std::make_pair(-1, vazio);
    }
    return make_pair(rand_value, rand_solution);
}

/**
 * Funcao base da busca local
**/
int local_search(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, std::string vizinhanca, std::string metodo)
{
    bool is_changing;
    std::vector<int> best_solution = initial_solution; 
    int it = 0, best_value = evaluate(adj_matrix, initial_solution);
    
    do
    {
        is_changing = false;
        std::vector<std::vector<int>> neighbours;
        if(vizinhanca.compare("adj") == 0)
            neighbours = genNeighbourhood(best_solution);
        else if(vizinhanca.compare("noAdj") == 0 && metodo.compare("best") == 0)
        {
            neighbours = genNeighbourhood_noAdj(best_solution);
        }

        int current_value;

        std::pair<int, std::vector<int> > neighbour;
        if(metodo.compare("best") == 0)
            neighbour = local_search_best_improvement(adj_matrix, neighbours, best_value);
        else if(metodo.compare("first") == 0)
            neighbour = local_search_first_improvement(adj_matrix, best_solution, best_value);
        else if(metodo.compare("random") == 0)
            neighbour = local_search_random_selection(adj_matrix, best_solution, best_value);

        if(neighbour.first != -1 && neighbour.first < best_value)
        {
            best_value = neighbour.first;
            best_solution = neighbour.second;
            is_changing = true;
        }
        it++;
    }while(is_changing);

    return best_value;
}