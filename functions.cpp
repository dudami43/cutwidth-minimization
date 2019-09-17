#include <bits/stdc++.h>
#include "functions.h"

/**
 * Funcao de avaliacao
**/ 
int evaluate(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution, std::string metodo)
{
    if(metodo.compare("max") == 0) // Retorna o corte que afeta o maior numero de arestas (max_cutwidth)
        return max_cutwidth_list(adj_list, solution).first;
    else if(metodo.compare("n_max") == 0) // Retorna o corte maximo multiplicado pela sua ocorrencia (n_max_cutwidth)
        return n_max_cutwidth_list(adj_list, solution).first;
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
 * Metrica para avaliar uma dada solucao
 * Avaliacao: eh retornado o corte com maior numero de arestas
**/
std::pair<int, std::vector<int>> max_cutwidth_list(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution)
{
    // Inicializa o vetor com os cortes entre os vertices
    std::vector<int> cuts;
    cuts.assign(solution.size() - 1, 0);

    // Calcula os cortes
    for(int i=0; i<solution.size(); i++){
        for(auto vertex_2: adj_list[solution[i]]){
            auto pos_vertex_2 = find(solution.begin()+i, solution.end(), vertex_2);
            if(pos_vertex_2 != solution.end()){
                for(int j=i; solution[j] != vertex_2; j++){
                    cuts[j]++;
                }
            }
        }
    }

    auto max_cut = std::max_element(cuts.begin(), cuts.end());
    return make_pair(*max_cut, cuts);
}

/**
 * Metrica para avaliar uma dada solucao
 * Avaliacao: eh retornado o corte com maior numero de arestas, multiplicado pelo
 * numero de vezes que ele acontece
**/
std::pair<int, std::vector<int>> n_max_cutwidth_list(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution)
{
    // Inicializa o vetor com os cortes entre os vertices
    std::vector<int> cuts;
    cuts.assign(solution.size() - 1, 0);

    // Calcula os cortes
    for(int i=0; i<solution.size(); i++){
        for(auto vertex_2: adj_list[solution[i]]){
            auto pos_vertex_2 = find(solution.begin()+i, solution.end(), vertex_2);
            if(pos_vertex_2 != solution.end()){
                for(int j=i; solution[j] != vertex_2; j++){
                    cuts[j]++;
                }
            }
        }
    }

    auto max_cut = std::max_element(cuts.begin(), cuts.end());
    int n_max_cut = std::count (cuts.begin(), cuts.end(), *max_cut);
    return make_pair(n_max_cut, cuts);
}

/**
 * Recalcula todos os cortes do grafo dado que ouve um MOVE ou um SWAP
**/
std::pair<int, std::vector<int>> reevaluate(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution, std::vector<int>& evaluate, bool swap, int val_1, int val_2){
    /*  
        Caso o movimento seja de swap, val1 = vertice 1 e val2 = vertice2
        Caso contratio, val1 = vertice 1 e val2 = nova localizacao do mesmo
    */

    // Decrementa 1 para cada corte que as arestas do vertice em
    // questao intercepta
    bool init_edge = false, end_edge = false;
    for(auto x: adj_list[solution[val_1]]){
        for(int i=0; i<solution.size(); i++){
            if(solution[i] == x || solution[i] == solution[val_1]){
                init_edge = true;
                evaluate[i]--;
                continue;
            }
            if(init_edge){
                if(solution[i] == x || solution[i] == solution[val_1]){
                    break;
                }
                evaluate[i]--;  
            }
        }
    }

    if(swap){
        // Decrementa 1 para cada corte que as arestas do segundo vertice
        // interceptam
        bool init_edge = false, end_edge = false;
        for(auto x: adj_list[solution[val_1]]){
            for(int i=0; i<solution.size(); i++){
                if(solution[i] == x || solution[i] == solution[val_1]){
                    init_edge = true;
                    evaluate[i]--;
                    continue;
                }
                if(init_edge){
                    if(solution[i] == x || solution[i] == solution[val_1]){
                        break;
                    }
                    evaluate[i]--;  
                }
            }
        }

        // Troca os elementos de lugar
        int value = solution[val_1];
        solution[val_1] = solution[val_2];
        solution[val_2] = solution[val_1];

        // Incrementa 1 para cada corte que as arestas do primeiro vertice,
        // na nova posicao, intercepta
        init_edge = false, end_edge = false;
        for(auto x: adj_list[solution[val_2]]){
            for(int i=0; i<solution.size(); i++){
                if(solution[i] == x || solution[i] == solution[val_2]){
                    init_edge = true;
                    evaluate[i]++;
                    continue;
                }
                if(init_edge){
                    if(solution[i] == x || solution[i] == solution[val_2]){
                        break;
                    }
                    evaluate[i]++;  
                }
            }
        }

    }else{
        // Troca o elemento para o novo lugar
        int value = solution[val_1];
        if(val_1 < val_2){
            // Caso o elemento se movimente pra frente, entao insira-o
            // na posicao desejada - 1
            auto pos = find(solution.begin(), solution.end(), solution[val_1]);
            solution.erase(pos);
            solution.insert(solution.begin()+(val_2 - 1), value);
        }else{
            // Caso o elemento se movimente pra tras, entao insira-o
            // na posicao desejada
            auto pos = find(solution.begin(), solution.end(), solution[val_1]);
            solution.erase(pos);
            solution.insert(solution.begin()+val_2, value);
        }
    }

    // Incrementa 1 para cada corte que as arestas do vertice,
    // na nova posicao, intercepta
    init_edge = false, end_edge = false;
    for(auto x: adj_list[solution[val_2]]){
        for(int i=0; i<solution.size(); i++){
            if(solution[i] == x || solution[i] == solution[val_2]){
                init_edge = true;
                evaluate[i]++;
                continue;
            }
            if(init_edge){
                if(solution[i] == x || solution[i] == solution[val_2]){
                    break;
                }
                evaluate[i]++;  
            }
        }
    }

    auto max_cut = std::max_element(evaluate.begin(), evaluate.end());
    return make_pair(*max_cut, evaluate);
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
 * Retorna todos os vizinhos de uma dada solucao
 * Vizinho: move e swap com probabilidade p
**/
std::vector<std::vector<int>> genNeighbourhood_ms(std::vector<int>& initial_solution, int limite_vertices)
{
    // Caso o numero de vertices no problema seja maior que o limite passado, adquire somente
    // o numero do limite de vizinhos
    std::vector<std::vector<int>> neighbours;
    int num_vizinhos;
    if(initial_solution.size() > limite_vertices)
    {
        // Seta numero de vizinhos
        num_vizinhos = 500;
    }
    else
    {
        num_vizinhos = initial_solution.size();
    }
    
    // Inicializa variaveis
    std::vector<std::pair<int, int>> usados;
    int init, end; int move, new_pos, val_move;
    std::pair<int, int> trade, trade_inv;

    // Reserva espaco para o vector de vizinhos
    neighbours.reserve(num_vizinhos);
    neighbours.reserve(2*num_vizinhos);

    int i=0;
    while(i < num_vizinhos)
    { 
        std::vector<int> aux(initial_solution);

        //------------------------move----------------------------------------------
        move = abs(rand() % initial_solution.size());
        new_pos = abs(rand() % initial_solution.size());
        val_move = aux[move];
        aux.erase(aux.begin()+move);
        aux.insert(aux.begin()+new_pos, val_move);

        //-----------------------swap-----------------------------------------------
        double p = ((double) rand() / (RAND_MAX));
        if(p >= 0.5)
        {
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
                int aux_swap = aux[init];
                aux[init] = aux[end];
                aux[end] = aux_swap;
                usados.push_back(trade); // Adiciona tupla de valores como ja utilizados
                usados.push_back(trade_inv);
                i++;
            }
        }
        neighbours.push_back(aux); // Adiciona vizinho na vizinhanca
    }
    return neighbours;
}

/**
 * Retorna o vizinho que tem a melhor solucao
 * Caso nenhum vizinho tenha solucao melhor que a atual, retorna -1
**/
std::pair<int, std::vector<int> > local_search_best_improvement(std::vector<std::vector<int> >& adj_list, std::vector<std::vector<int> >& neighbours, int best_value)
{
    std::vector<int> best_solution; 
    int current_value, initial_value = best_value;
    for(int i = 0; i < neighbours.size(); i++)
    {
        current_value = evaluate(adj_list, neighbours[i]);
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
std::pair<int, std::vector<int> > local_search_first_improvement(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, int best_value)
{
    std::vector<int> best_solution = initial_solution; 
    int init;
    int end;
    int current_value = best_value;
    bool improved = false; 
    int iterations = 100;
    int i = 0;
    while(!improved && i < iterations)
    {
        init = abs(rand() % initial_solution.size());
        end = abs(rand() % initial_solution.size());

        int aux_swap = initial_solution[init];
        initial_solution[init] = initial_solution[end];
        initial_solution[end] = aux_swap;

        current_value = evaluate(adj_list, initial_solution);
        if(current_value < best_value)
        {
            best_solution = initial_solution;
            best_value = current_value;
            improved = true;
        }
        i++;
    }
    return std::make_pair(best_value, best_solution);
}

/**
 * Retorna um vizinho aleatorio
**/
std::pair<int, std::vector<int> >  local_search_random_selection(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, int best_value)
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
    int rand_value = evaluate(adj_list, rand_solution);

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
int local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca, std::string metodo)
{
    bool is_changing;
    std::vector<int> best_solution = initial_solution; 
    int best_value = evaluate(adj_list, initial_solution);
    
    do
    {
        is_changing = false;
        std::vector<std::vector<int>> neighbours;
        if(vizinhanca.compare("adj") == 0)
        {
            neighbours = genNeighbourhood(best_solution);
        }
        else if(vizinhanca.compare("noAdj") == 0 && metodo.compare("best") == 0)
        {
            neighbours = genNeighbourhood_noAdj(best_solution);
        }
        else if(vizinhanca.compare("ms") == 0 && metodo.compare("best") == 0)
        {
            neighbours = genNeighbourhood_ms(best_solution);
        }

        int current_value;

        std::pair<int, std::vector<int> > neighbour;
        if(metodo.compare("best") == 0)
            neighbour = local_search_best_improvement(adj_list, neighbours, best_value);
        else if(metodo.compare("first") == 0)
            neighbour = local_search_first_improvement(adj_list, best_solution, best_value);
        else if(metodo.compare("random") == 0)
            neighbour = local_search_random_selection(adj_list, best_solution, best_value);

        if(neighbour.first != -1 && neighbour.first < best_value)
        {
            best_value = neighbour.first;
            best_solution = neighbour.second;
            is_changing = true;
        }
    }while(is_changing);

    return best_value;
}

/**
 * Funcao gulosa que adquire uma solucao inicial
**/ 
std::vector<int> first_solution(std::vector<std::vector<int> >& adj_list, bool random){

    // Lanca excecao caso haja 1 ou menos vertices na lista de adjacencia
    if(adj_list.size() < 2)
        throw;
    
    // Inicializa o vector que contera a solucao(initial_solution)
    // e o vector com os indices, de cada vertice, que serao
    // ordenados por ordem de maior numero de adjacencias
    std::vector<int> initial_solution, index_sort;
    for(int i=0; i<adj_list.size(); i++)
        index_sort.push_back(i);
    
    
    if(random){
        // Embaralha a lista de indices e depois os ordena(com excessao dos dois ultimos)
        for(int i=0; i<5; i++)
            std::random_shuffle( index_sort.begin(), index_sort.end());
        std::sort(index_sort.begin(), index_sort.end() - 2, [&](int i, int j) { return adj_list[i].size() < adj_list[j].size(); } );
    }else{
        // Ordena a lista de indices com base no numero de adjacencias
        // em cada vertice da lista de adjacencia
        std::sort(index_sort.begin(), index_sort.end(), [&](int i, int j) { return adj_list[i].size() < adj_list[j].size(); } );
    }

    /**
     * Ideia do algoritmo guloso:
     * Colocar os dois vertices que mais tem grau de entrada/saida no meio
     * Ir alocando os outros em uma das três posições: antes, entre e depois dos vertices
     * que ja estao alocados de maneira a igualar os numeros de arestas que saem/entram
     * do lado de esquero e do lado direito de cada vertice
    **/

    // Adiciona os dois elementos com maior grau de entrada/saida
    initial_solution.push_back(index_sort[index_sort.size()-2]);
    initial_solution.push_back(index_sort[index_sort.size()-1]);

    // Remove os mesmos dos indices ordenados
    index_sort.pop_back();
    index_sort.pop_back();

    // Enquanto ainda ha elemento no vector de indices
    int i = 0;
    while(index_sort.size() > 0){
        std::vector<int> linked;
        linked.reserve(initial_solution.size()); 
        
        // Adquire todos os vertices que estao interligados ao vertice atual
        for(int j=0; j<initial_solution.size(); j++){
            auto pos = std::find(adj_list[initial_solution[j]].begin(), adj_list[initial_solution[j]].end(), index_sort[i]);
            if(pos != adj_list[initial_solution[j]].end()){
                linked.push_back(initial_solution[j]);
            }
        }

        /** 
         * Coloca o vertice na posicao calculada da seguinte maneira:
         * * Caso o mesmo tenha apenas um vertice interligado(que ja esta alocado)
         *   entao o vertice sera alocado ao lado dele (no lado que tem menos vertices)
         * * Caso tenha mais de um vertice interligado(ja alocados)
         *   entao o vertice sera colocado entre eles
         * * Caso nao tenha nenhum vertice interligado(alocado)
         *   nada sera feito
        **/
        if(linked.size() > 1){
            int sum = 0, pos_it;
            for(auto x: linked){
                auto it = std::find(initial_solution.begin(), initial_solution.end(), x);
                pos_it = std::distance(initial_solution.begin(), it);
                sum += pos_it;
            }
            sum /= linked.size();
            initial_solution.insert(initial_solution.begin()+sum, index_sort[i]);
        }else if(linked.size() == 1){
            auto it = std::find(initial_solution.begin(), initial_solution.end(), linked[0]);
            int pos_it = std::distance(initial_solution.begin(), it);
            if(pos_it > initial_solution.size()/2){ 
                if(linked[0] == *(initial_solution.rbegin())){
                    // Caso o elemento seja o ultimo da solucao
                    // insere no final
                    initial_solution.insert(initial_solution.end(), index_sort[i]);
                }else{
                    // Caso ele esteja no final da solucao mas nao seja o ultimo
                    // inserir apos o elemento
                    initial_solution.insert(it+1, index_sort[i]);
                }
            }else {
                // Caso ele esteja no inicio da solucao
                // inserir antes do elemento
                initial_solution.insert(it, index_sort[i]);
            }
        }else{
            // Caso nao haja nenhum vertice, alocado, que se interligue
            // no vertice atual, apenas passe para frente
            i = (i+1) % index_sort.size();
            continue;
        }

        // Retira o vertice do vector de indices
        index_sort.erase(index_sort.begin() + i);

        if(index_sort.size() > 0){
            i = (i+1) % index_sort.size();
        }
    }

    /*
    for(auto x: initial_solution){
        std::cout << x << " ";
    }
    std::cout << std::endl; */

    return initial_solution;
}

/**
 * Simulated annealing padrão: parâmetros são passados na chamada
 * valores default:
 * temp_init = 120, temp_min = 1, cooling = 0.99, itermax = 
 */
int simulated_annealing(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, double temp_init, double temp_min, double cooling, int itermax, bool move_and_swap)
{
    std::vector<int> current_solution = initial_solution; 
    std::vector<int> best_solution = initial_solution; 
    std::vector<int> iter_solution = initial_solution; 
    int current_value = evaluate(adj_list, initial_solution); 
    int best_value = current_value;
    double temp = temp_init;
    int iterations_without_improve = 0, it = 0;
    while (temp > temp_min)
    {
        it = 0;
        while(iterations_without_improve < 10 || it < itermax)
        {
            int init = abs(rand() % initial_solution.size());
            int end = abs(rand() % initial_solution.size());
            
            std::vector<int> iter_solution(current_solution);

            if(!move_and_swap)
            {
                int aux_swap = iter_solution[init];
                iter_solution[init] = iter_solution[end];
                iter_solution[end] = aux_swap;
            }
            else
            {

                //------------------------move----------------------------------------------
                int move = abs(rand() % initial_solution.size());
                int new_pos = abs(rand() % initial_solution.size());
                int val_move = iter_solution[move];
                iter_solution.erase(iter_solution.begin()+move);
                iter_solution.insert(iter_solution.begin()+new_pos, val_move);

                //-----------------------swap-----------------------------------------------
                double p = ((double) rand() / (RAND_MAX));
                if(p >= 0.5)
                {
                    // Adquire dois numeros aleatorios para representarem os vertices que trocarao de lugar
                    init = abs(rand() % initial_solution.size());
                    end = abs(rand() % initial_solution.size());
                    //std::cout << i << " " << init << " " << end << std::endl;           
                    int aux_swap = iter_solution[init];
                    iter_solution[init] = iter_solution[end];
                    iter_solution[end] = aux_swap;
                }
            }       

            double p = ((double) rand() / (RAND_MAX));

            int iter_val = evaluate(adj_list, iter_solution);

            if(iter_val < current_value)
            {
                current_solution = iter_solution;
                current_value = iter_val;
                if(iter_val < best_value)
                {
                    best_solution = iter_solution;
                    best_value = iter_val;
                }
                iterations_without_improve = 0;
            }
            else{
                if(exp((current_value - iter_val)/temp) >= p)
                {
                    current_solution = iter_solution;
                    current_value = iter_val;
                }
                iterations_without_improve++;
            }
            it++;
        }
        temp = temp * cooling;
        iterations_without_improve = 0;
    }
    return best_value;
}

/*
* Executar o simulated annealing várias vezes para encontrar a melhor solução
*/
int best_simulated_annealing(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution)
{
    int best_value = evaluate(adj_list, initial_solution); 
    int iter_value;
    int i = 0, imax = 100;
    while(i < imax)
    {
        iter_value = simulated_annealing(adj_list, initial_solution);
        if(iter_value < best_value)
        {
            best_value = iter_value;
        }
        i++;
    }
    return best_value;   
}

/**
 * Busca local que retorna a solução ao invés de somente seu valor, utilizada em outras funções como ILS e GRASP
**/ 
std::vector<int> local_search_aux(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca)
{
    bool is_changing;
    std::vector<int> best_solution = initial_solution; 
    int best_value = evaluate(adj_list, initial_solution);
    
    do
    {
        is_changing = false;
        /*std::vector<std::vector<int>> neighbours;
        if(vizinhanca.compare("adj") == 0)
            neighbours = genNeighbourhood(best_solution);
        else if(vizinhanca.compare("noAdj") == 0)
        {
            neighbours = genNeighbourhood_noAdj(best_solution);
        }
        else if(vizinhanca.compare("ms") == 0)
        {
            neighbours = genNeighbourhood_ms(best_solution);
        }
        */
        int current_value;

        std::pair<int, std::vector<int> > neighbour;
        neighbour = local_search_first_improvement(adj_list, best_solution, best_value);
        //neighbour = local_search_best_improvement(adj_list, neighbours, best_value);
        
        if(neighbour.first != -1 && neighbour.first < best_value)
        {
            best_value = neighbour.first;
            best_solution = neighbour.second;
            is_changing = true;
        }
    }while(is_changing);

    return best_solution;
}

/**
 * Pertubação usada no ILS
**/ 
std::vector<int> pertubation(std::vector<int> solution, int level)
{
    int number_xchanges = level;
    int init, end;
    for(int i = 1; i < number_xchanges; i++)
    {
        init = abs(rand() % solution.size());
        end = abs(rand() % solution.size());
        int aux_swap = solution[init];
        solution[init] = solution[end];
        solution[end] = aux_swap;
    }
    return solution;
}

/**
 * ILS padrão
**/ 
int iterated_local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca)
{
    std::vector<int> best_solution = local_search_aux(adj_list, initial_solution, vizinhanca); 
    std::vector<int> pert_solution, iter_solution;
    int best_value = evaluate(adj_list, best_solution); int iter_value;
    int iter = 0;
    int itermax = 0, imax = 100;
    int melhor_iter = iter;
    int level = 1;
    while(iter - melhor_iter < imax)
    {
        iter++;
        pert_solution = pertubation(best_solution, level);
        iter_solution = local_search_aux(adj_list, pert_solution, vizinhanca);
        iter_value = evaluate(adj_list, iter_solution);

        if(iter_value < best_value)
        {
            best_solution = iter_solution;
            best_value = iter_value;
            melhor_iter = iter;
            level = 1;
        }
        else
        {
            level++;
        }
    }
    return best_value;   
}

/**
 * Smart ILS
**/ 
int smart_iterated_local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca)
{
    std::vector<int> best_solution = local_search_aux(adj_list, initial_solution, vizinhanca); 
    std::vector<int> pert_solution, iter_solution;
    int best_value = evaluate(adj_list, best_solution); int iter_value;
    int iter = 0;
    int imax = 100, vmax = 10;
    int melhor_iter = iter;
    int level = 1, nvezes = 1;
    while(iter - melhor_iter < imax)
    {
        iter++;
        pert_solution = pertubation(best_solution, level);
        iter_solution = local_search_aux(adj_list, pert_solution, vizinhanca);
        iter_value = evaluate(adj_list, iter_solution);

        if(iter_value < best_value)
        {
            best_solution = iter_solution;
            best_value = iter_value;
            melhor_iter = iter;
            level = 1;
            nvezes = 1;
        }
        else
        {
            if(nvezes >= vmax) // só aumenta o nível de pertubação após algumas tentativas sem sucesso, para o caso da região não ter sido explorada adequadamente
            {
                level++;
                nvezes = 1;
            }
            else{
                nvezes++;
            }
        }
    }
    return best_value;   
}

int grasp(std::vector<std::vector<int> >& adj_list, std::string neighbourhood, std::string method, int n_iterations, int path_relinking_size){
    /*
        Enquanto (condição de parada não for satisfeita), faça
            solução = crie aleatoriamente uma solução de forma construtiva();
            solução = busca local(solução);
            se solução é a melhor solução até então conhecida então
                grave(solução);
            fim se
        Fim Enquanto
    */

    std::vector<int> initial_solution = first_solution(adj_list, true);
    int value = local_search(adj_list, initial_solution, "noAdj", "best");
    int best_value = value;
    for(int i=1; i < n_iterations; i++){
            std::vector<int> initial_solution = first_solution(adj_list, true);
            int value = local_search(adj_list, initial_solution, "noAdj", "best");
    }
    return best_value;
}

/**
 * Funcao que testa se a funcao de avaliacao esta correta 
**/
bool testa_evaluate(std::vector<std::vector<int> >& adj_matrix, std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution){
    // Inicializa variaveis
    int init, end;
    std::pair<int,std::vector<int>> result_evaluate_init = max_cutwidth_list(adj_list, initial_solution);

    // Adquire dois numeros aleatorios para representarem os vertices que trocarao de lugar
    init = abs(rand() % initial_solution.size());
    end = abs(rand() % initial_solution.size());
    
    // Gera swap aleatorio
    std::vector<int> rand_solution(initial_solution);
    int rand_solution_swap = rand_solution[init];
    rand_solution[init] = rand_solution[end];
    rand_solution[end] = rand_solution_swap;

    // Avalia a solucao adquirida
    int result_evaluate = max_cutwidth(adj_matrix, rand_solution);
    std::pair<int,std::vector<int>> result_evaluate_list = max_cutwidth_list(adj_list, rand_solution);

    std::cout << std::endl;
    std::cout << "Evaluate: " << result_evaluate<< std::endl;
    std::cout << "Reevaluate: " << result_evaluate_list.first << std::endl;

    if(result_evaluate == result_evaluate_list.first)
        return true;
    else return false;
}

/**
 * Funcao que testa se a funcao de reavaliacao esta correta 
**/
bool testa_reevaluate(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution){
    // Inicializa variaveis
    int init, end;
    std::pair<int,std::vector<int>> result_evaluate_init = max_cutwidth_list(adj_list, initial_solution);

    // Adquire dois numeros aleatorios para representarem os vertices que trocarao de lugar
    init = abs(rand() % initial_solution.size());
    end = abs(rand() % initial_solution.size());
    
    // Gera swap aleatorio
    std::vector<int> rand_solution(initial_solution);
    int rand_solution_swap = rand_solution[init];
    rand_solution[init] = rand_solution[end];
    rand_solution[end] = rand_solution_swap;

    // Avalia a solucao adquirida
    std::pair<int,std::vector<int>> result_evaluate = max_cutwidth_list(adj_list, rand_solution);
    std::pair<int,std::vector<int>> result_reevaluate = reevaluate(adj_list, initial_solution, result_evaluate_init.second, false, init, end);

    std::cout << std::endl;
    std::cout << "Evaluate: " << result_evaluate.first << std::endl;
    for(auto x: result_evaluate.second){
        std::cout << x << " ";
    }std::cout << std::endl;
    std::cout << "Reevaluate: " << result_reevaluate.first << std::endl;
    for(auto x: result_reevaluate.second){
        std::cout << x << " ";
    }std::cout << std::endl;

    if(result_evaluate.first == result_reevaluate.first)
        return true;
    else return false;
}
