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
            // Adquire dois numeros aleatorios para representarem os vertices que trocarao de lugar
            init = abs(rand() % initial_solution.size());
            end = abs(rand() % initial_solution.size());
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
    std::vector<int> best_solution(initial_solution);
    std::vector<int> aux_solution(initial_solution);
    int init;
    int end;
    int current_value = best_value;
    bool improved = false; 
    int iterations = 100;
    int i = 0;
    while(!improved && i < iterations)
    {
        init = abs(rand() % aux_solution.size());
        end = abs(rand() % aux_solution.size());

        int aux_swap = aux_solution[init];
        aux_solution[init] = aux_solution[end];
        aux_solution[end] = aux_swap;

        current_value = evaluate(adj_list, aux_solution);
        if(current_value < best_value)
        {
            best_solution = aux_solution;
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

    // Adquire dois numeros aleatorios para representarem os vertices que trocaralocal_search_first_improvemento de lugar
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
std::pair<int, std::vector<int> > local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca, std::string metodo)
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

    return make_pair(best_value, best_solution);
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
        /* // Embaralha a lista de indices e depois os ordena(com excessao dos dois ultimos)
        for(int i=0; i<5; i++)
            std::random_shuffle( index_sort.begin(), index_sort.end());
        std::sort(index_sort.begin(), index_sort.end() - 2, [&](int i, int j) { return adj_list[i].size() < adj_list[j].size(); } ); */

        // Embaralha a lista de indices e depois os ordena(com excessao dos dois ultimos)
        std::sort(index_sort.begin(), index_sort.end(), [&](int i, int j) { return adj_list[i].size() < adj_list[j].size(); } );
        for(int i=0; i<5; i++){
            std::random_shuffle(index_sort.begin()+(3*index_sort.size()/4), index_sort.end()); //Embaralha os 25% vertices com mais arestas
        }
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

    // Caso o metodo seja randomico, reordena a parte embaralhada que nao foi retirada
    if(random){
        std::sort(index_sort.begin()+(3*index_sort.size()/4), index_sort.end(), [&](int i, int j) { return adj_list[i].size() < adj_list[j].size(); } );
    }

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

    return initial_solution;
}

/**
 * Simulated annealing padrão: parâmetros são passados na chamada
 * valores default:
 * temp_init = 120, temp_min = 1, cooling = 0.99, itermax = 120
 */
std::pair<int, std::vector<int> > simulated_annealing(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, double temp_init, double temp_min, double cooling, int itermax, bool move_and_swap)
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
    return make_pair(best_value, best_solution);
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
 * Smart ILS
**/ 
int smart_iterated_local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca, int imax, int vmax)
{
    std::pair<int, std::vector<int> > result = local_search(adj_list, initial_solution, vizinhanca); 
    std::pair<int, std::vector<int> > iter_result;

    std::vector<int> best_solution = result.second;
    std::vector<int> pert_solution, iter_solution;
    
    int best_value = result.first; 
    int iter_value;

    int iter = 0;
    int itermax = 0;
    int melhor_iter = iter;
    int level = 1, nvezes = 1;
    
    while(iter - melhor_iter < imax)
    {
        iter++;
        pert_solution = pertubation(best_solution, level);
        iter_result = local_search(adj_list, pert_solution, vizinhanca);
        iter_solution = iter_result.second;
        iter_value = iter_result.first;

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
            if(nvezes >= vmax) //smart: só aumenta o nível de pertubação após algumas tentativas sem sucesso, para o caso da região não ter sido explorada adequadamente
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

/**
 * Calcula o proximo passo da solucao atual ate a solucao elite em questao
**/ 
std::vector<int> next_step(std::vector<int>& elite_solution, std::vector<int>& current_solution){
    std::vector<int> step(current_solution);
    for(int i=0; i<elite_solution.size(); i++){
        // Procura uma posicao que contem vertices diferentes
        // nas solucoes
        if(elite_solution[i] != step[i]){
            int aux = elite_solution[i];
            // Procura posicao do vertice que difere no passo step
            auto pos = find(step.begin(), step.end(), aux);
            // Troca a ordem dos mesmos no step
            *pos = step[i];
            step[i] = aux;
            break;
        }
    }
    return step;
}

/**
 * Compara duas solucoes
**/ 
bool compare_solution(std::vector<int>& solution_1, std::vector<int>& solution_2){
    if(solution_1.size() != solution_2.size()) return false;
    else{
        for(int i=0; i<solution_1.size(); i++){
            if(solution_1[i] != solution_2[i]) return false;
        }
    }
    return true;
}

int grasp(std::vector<std::vector<int> >& adj_list, std::string neighbourhood, std::string method, int n_iterations, int path_relinking_size){

    std::vector<std::pair<int, std::vector<int> > > elite_solutions;
    elite_solutions.reserve(path_relinking_size);

    // Adquire a primeira solucao inicial
    std::vector<int> initial_solution = first_solution(adj_list, true);
    std::pair<int, std::vector<int> > value = local_search(adj_list, initial_solution, "noAdj", "best");
    
    // Seta os valores da solucao inicial como os melhores ate agora
    int best_value = value.first;
    std::vector<int> best_solution = value.second;
    
    // Adiciona a solucao inicial ao path relink
    elite_solutions.push_back(make_pair(best_value, best_solution));

    // Comeca o GRASP
    for(int i=1; i < n_iterations; i++){
        // Adquire uma solucao e melhora a mesma com busca local
        std::vector<int> initial_solution = first_solution(adj_list, true);
        value = local_search(adj_list, initial_solution, "noAdj", "best");
        
        // Caso a solucao encontrada seja a melhor ate o momento
        // seta a mesma como a melhor
        if(value.first < best_value){
            best_value = value.first;
            best_solution = value.second;
        }

        // Se ainda esta na fase de construcao do path_relink
        if(i < path_relinking_size){
            // Adiciona a solucao encontrada ao path
            elite_solutions.push_back(make_pair(value.first, value.second));
        }else{
            // Seleciona uma solucao aleatoria
            int rand_index = abs(rand() % elite_solutions.size());
            std::vector<int> rand_elite_solution = elite_solutions[rand_index].second;
            std::vector<int> aux_solution = value.second;

            // Ordena as solucoes elite em ordem crescente de avaliacao
            std::sort(elite_solutions.begin(), elite_solutions.end());

            int best_aux_value = (*elite_solutions.rbegin()).first;
            std::vector<int> best_aux_solution = (*elite_solutions.rbegin()).second;

            // Enquanto nao chegou na solucao elite, adquire mais um passo
            while(!compare_solution(rand_elite_solution, aux_solution)){
                
                // Adquire o proximo passo ate a solucao elite
                aux_solution = next_step(rand_elite_solution, aux_solution);
                int aux_value = evaluate(adj_list, aux_solution);

                // Se esse passo for melhor que a solucao elite
                if(aux_value < best_aux_value){
                    best_aux_value = aux_value;
                    best_aux_solution = aux_solution;
                }

            }

            // Se o passo de melhor valor for melhor que a melhor solucao encontrada
            // seta o melhor passo como a melhor solucao e substitui a pior solucao elite
            if(best_aux_value < best_value){
                
                best_value = best_aux_value;
                best_solution = aux_solution;

                // Remove pior solucao elite
                elite_solutions.pop_back();
                // Adiciona o melhor passo a solucao elite
                elite_solutions.push_back(make_pair(best_aux_value, aux_solution));
                // Reordena as solucoes elite em ordem crescente de avaliacao
                std::sort(elite_solutions.begin(), elite_solutions.end());

            // Se o melhor passo for pior que a melhor solucao, porem melhor que 
            // alguma solucao elite, entao substitui a pior solucao elite
            }else if(best_aux_value < (*elite_solutions.rbegin()).first){
                // Remove pior solucao elite
                elite_solutions.pop_back();
                // Adiciona o melhor passo a solucao elite
                elite_solutions.push_back(make_pair(best_aux_value, aux_solution));
                // Reordena as solucoes elite em ordem crescente de avaliacao
                std::sort(elite_solutions.begin(), elite_solutions.end());
            }
        }
    }
    return best_value;
}

/**
 * Executar uma heurística várias vezes para encontrar a melhor solução
**/
int best_solution(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string meta)
{
    int best_value = evaluate(adj_list, initial_solution); 
    int iter_value;
    int i = 0, imax = 10;
    if(meta.compare("sa") == 0)
    {
        while(i < imax)
        {
            auto start = std::chrono::high_resolution_clock::now(); 
            iter_value = simulated_annealing(adj_list, initial_solution).first;
            auto end = std::chrono::high_resolution_clock::now();

            // Calculating total time taken by the program. 
            double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
            time_taken *= 1e-9;

            std::cout << iter_value << "," << std::fixed  << time_taken << std::setprecision(9) << std::endl;

            if(iter_value < best_value)
            {
                best_value = iter_value;
            }
            i++;
        }
    }
    else if(meta.compare("sils") == 0)
    {
        while(i < imax)
        {
            auto start = std::chrono::high_resolution_clock::now(); 
            iter_value = smart_iterated_local_search(adj_list, initial_solution);
            auto end = std::chrono::high_resolution_clock::now();

            // Calculating total time taken by the program. 
            double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
            time_taken *= 1e-9;

            std::cout << iter_value << "," << std::fixed  << time_taken << std::setprecision(9) << std::endl;
            
            if(iter_value < best_value)
            {
                best_value = iter_value;
            }
            i++;
        }

    }  
    else if(meta.compare("grasp") == 0)
    {
        while(i < imax)
        {
            auto start = std::chrono::high_resolution_clock::now(); 
            iter_value = grasp(adj_list);
            auto end = std::chrono::high_resolution_clock::now();

            // Calculating total time taken by the program. 
            double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
            time_taken *= 1e-9;

            std::cout << iter_value << "," << std::fixed  << time_taken << std::setprecision(9) << std::endl;
            
            if(iter_value < best_value)
            {
                best_value = iter_value;
            }
            i++;
        }
    }  
    return best_value;   
}