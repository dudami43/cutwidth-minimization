int evaluate(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution, std::string metodo = "max");
int max_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution);
int n_max_cutwidth(std::vector<std::vector<int> >& adj_matrix, std::vector<int>& solution);

std::pair<int, std::vector<int>> max_cutwidth_list(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution);
std::pair<int, std::vector<int>> n_max_cutwidth_list(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution);
std::pair<int, std::vector<int>> reevaluate(std::vector<std::vector<int> >& adj_list, std::vector<int>& solution, std::vector<int>& evaluate, bool swap, int val_1, int val_2);

std::vector<std::vector<int> > genNeighbourhood(std::vector<int>& initial_solution);
std::vector<std::vector<int> > genNeighbourhood_noAdj(std::vector<int>& initial_solution, int limite_vertices = 25);
std::vector<std::vector<int>> genNeighbourhood_ms(std::vector<int>& initial_solution, int limite_vertices = 25);

std::pair<int, std::vector<int> > local_search_best_improvement(std::vector<std::vector<int>>& adj_list, std::vector<std::vector<int>>& neighbours, int best_value);
std::pair<int, std::vector<int> > local_search_first_improvement(std::vector<std::vector<int>>& adj_list, std::vector<int>& initial_solution, int best_value);
std::pair<int, std::vector<int> >  local_search_random_selection(std::vector<std::vector<int>>& adj_list, std::vector<int>& initial_solution, int best_value);

int local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca = "adj", std::string metodo = "first");

std::vector<int> first_solution(std::vector<std::vector<int> >& adj_list, bool random = false);

int simulated_annealing(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, double temp_init = 120, double temp_min = 1, double cooling = 0.99, int itermax = 100, bool move_and_swap = true);

std::vector<int> local_search_aux(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca);
std::vector<int> pertubation(std::vector<int> solution, int level);
int iterated_local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca, int imax = 100);
int smart_iterated_local_search(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution, std::string vizinhanca, int imax = 100, int vmax = 10);

int grasp(std::vector<std::vector<int> >& adj_list, std::string neighbourhood, std::string method, int n_iterations, int path_relinking_size);

bool testa_reevaluate(std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution);
bool testa_evaluate(std::vector<std::vector<int> >& adj_matrix, std::vector<std::vector<int> >& adj_list, std::vector<int>& initial_solution);