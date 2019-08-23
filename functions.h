int evaluate(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& solution);
std::vector<std::vector<int>> genNeighbourhood(std::vector<int>& initial_solution);
int local_search(std::vector<std::vector<int>>& adj_matrix, std::vector<int>& initial_solution);