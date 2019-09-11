int evaluate(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution, std::string metodo = "max");
int max_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution);
int mean_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution);
int n_max_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution);

std::vector<std::vector<int> > genNeighbourhood(std::vector<int>& initial_solution);
std::vector<std::vector<int> > genNeighbourhood_noAdj(std::vector<int>& initial_solution, int limite_vertices = 25);
std::vector<std::vector<int>> genNeighbourhood_ms(std::vector<int>& initial_solution, int limite_vertices = 25);

std::pair<int, std::vector<int> > local_search_best_improvement(std::vector<std::vector<int>>& adj_matrix, std::vector<std::vector<int>>& neighbours, int best_value);
std::pair<int, std::vector<int> > local_search_first_improvement(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& initial_solution, int best_value);
std::pair<int, std::vector<int> >  local_search_random_selection(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& initial_solution, int best_value);

int local_search_duda(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution);
int local_search(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, std::string vizinhanca = "adj", std::string metodo = "first");

std::vector<int> first_solution(std::vector<std::vector<int> >& adj_list);

int simulated_annealing(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, double temp_init, double temp_min, double cooling, bool move_and_swap);

std::vector<int> local_search_aux(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, std::string vizinhanca);
std::vector<int> pertubation(std::vector<int> solution);
int iterated_local_search(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& initial_solution, std::string vizinhanca);
