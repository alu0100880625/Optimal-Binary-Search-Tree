#include "../include/optimal_binary_search_tree_t.hpp"

int main(void)
{
 optimal_binary_search_tree_t<int> obst("input/input.txt");
 obst.solve();
}
/*
int main(void)
{
 matrix_t<int> matrix;
 std::cin >> matrix;
 std::cout << matrix;
 
}
*/
/*
int main(void)
{
  matrix_t<int> matriz(5, 9);
  int x = 0;
  for(int i = 0; i < matriz.get_rows(); i++)
    for(int j = 0; j < matriz.get_columns(); j++)
      matriz(i, j) = x++;
  std::cout << matriz <<std::endl;
}
*/