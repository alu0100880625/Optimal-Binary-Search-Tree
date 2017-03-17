#include "../include/optimal_binary_search_tree_t.hpp"

int main(void)
{
  typedef char problem_type;

  optimal_binary_search_tree_t<problem_type> obst("input/input.txt");
  //obst.solve_bottom_up();
  obst.solve_dynamic_programming();
  //std::cout << obst.reconstruct() << std::endl;
}
