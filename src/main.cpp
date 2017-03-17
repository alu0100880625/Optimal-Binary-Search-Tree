#include "../include/optimal_binary_search_tree_t.hpp"

int main(void)
{
  typedef char problem_type;

  optimal_binary_search_tree_t<problem_type> obst("input/input.txt");
  obst.solve();

  std::cout << obst.reconstruct() << std::endl;
}
