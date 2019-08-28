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
std::vector<std::vector<int>> genNeighbourhood_noAdj(std::vector<int>& initial_solution, int limite)
{
    std::vector<std::vector<int>> neighbours;
    neighbours.reserve(initial_solution.size()*initial_solution.size()/2);

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

    if(neighbours.size() > limite){
        
        std::vector<std::vector<int>> neighbours_filtered;
        neighbours_filtered.reserve(limite);
        std::vector<int> usados;

        // Adquire uma semente a partir do horario do sistema
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand0 generator (seed); // Inicializa o gerador
        int rand_int;
        
        for(int i=0; i<limite; i++){    
            // Adquire vizinho aleatorio de acordo com o gerador de numeros aleatorios
            rand_int = abs(generator() % neighbours.size());
            auto pos = find(usados.begin(), usados.end(), rand_int);
            if(pos == usados.end()){
                neighbours_filtered.push_back(neighbours[rand_int]);
                usados.push_back(rand_int);
            }else{
                i--;
            }
        }
        
        return neighbours_filtered;
    }else
        return neighbours;
}

/**
 * Retorna o vizinho que tem a melhor solucao
 * Caso nenhum vizinho tenha solucao melhor que a atual, retorna -1
**/
std::pair<int, std::vector<int>> local_search_best_improvement(std::vector<std::vector<int> >& adj_matrix, std::vector<std::vector<int> >& neighbours, int best_value)
{
    std::vector<int> best_solution; 
    int current_value, initial_value = best_value;
    for(int i = 0; i < neighbours.size(); i++)
    {
        //std::cout<< i << '/' << neighbours.size() << " - num vertices: " << neighbours[i].size() << std::endl;
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
std::pair<int, std::vector<int> > local_search_first_improvement(std::vector<std::vector<int> >& adj_matrix, std::vector<std::vector<int> >& neighbours, int best_value)
{
    int current_value;
    for(int i = 0; i < neighbours.size(); i++)
    {                       
        current_value = evaluate(adj_matrix, neighbours[i]);
        if(current_value < best_value)
        {
            return std::make_pair(best_value, neighbours[i]);
        }
    }
    std::vector<int> vazio;
    return std::make_pair(-1, vazio);
}

/**
 * Retorna um vizinho aleatorio
**/
std::pair<int, std::vector<int> >  local_search_random_selection(std::vector<std::vector<int> >& adj_matrix, std::vector<std::vector<int> >& neighbours)
{
    // Adquire uma semente a partir do horario do sistema
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed); // Inicializa o gerador
    
    // Adquire vizinho aleatorio de acordo com o gerador de numeros aleatorios
    int rand_int = abs(generator() % neighbours.size());
    std::vector<int> rand_solution = neighbours[rand_int];
    int rand_value = evaluate(adj_matrix, rand_solution);
    
    return make_pair(rand_value, rand_solution);
}

/**
 * Implementacao da Duda
**/
int local_search_duda(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution)
{
    bool is_changing = false;
    std::vector<int> best_solution = initial_solution; 
    int best_value = evaluate(adj_matrix, initial_solution);
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

/**
 * Funcao base da busca local
**/
int local_search(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, std::string vizinhanca, std::string metodo, int iteration)
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
        else if(vizinhanca.compare("noAdj") == 0)
            neighbours = genNeighbourhood_noAdj(best_solution);

        int current_value;

        std::pair<int, std::vector<int> > neighbour;
        if(metodo.compare("best") == 0)
            neighbour = local_search_best_improvement(adj_matrix, neighbours, best_value);
        else if(metodo.compare("first") == 0)
            neighbour = local_search_first_improvement(adj_matrix, neighbours, best_value);
        else if(metodo.compare("random") == 0)
            neighbour = local_search_random_selection(adj_matrix, neighbours);

        if(neighbour.first != -1 && neighbour.first < best_value)
        {
            best_value = neighbour.first;
            best_solution = neighbour.second;
            is_changing = true;
        }
        it++;
    }while(is_changing && it < iteration);

    return best_value;
}