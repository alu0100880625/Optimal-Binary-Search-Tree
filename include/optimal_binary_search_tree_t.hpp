#pragma once
#include "matrix_t.hpp"
#include "vector_t.hpp"

#include <fstream>
#include <cstring>
#include <limits>

typedef float obst_frequency_t;
typedef int obst_inx_t;

template <class type_t>
class optimal_binary_search_tree_t
{
  private:
    matrix_t<obst_frequency_t> costs_;
    vector_t<obst_frequency_t> frequency_;
    vector_t<type_t> keys_;
  public:
    optimal_binary_search_tree_t(std::string file_name);
    ~optimal_binary_search_tree_t(void);
    
    void solve(void);
    
    private:
      obst_frequency_t sum(obst_inx_t lower_limit, obst_inx_t upper_limit) const;
};

template <class type_t>
optimal_binary_search_tree_t<type_t>::optimal_binary_search_tree_t(std::string file_name):
  costs_(),
  frequency_(),
  keys_()
  {
    std::ifstream file;
    file.open(file_name);
    if(file.is_open())
    {
      obst_inx_t size;
      file >> (obst_inx_t &) size;
      costs_.resize(size, size);
      frequency_.resize(size);
      keys_.resize(size);
      for(obst_inx_t i = 0; i < size; i++)
        file >> (type_t &) keys_[i];
      for(obst_inx_t i = 0; i < size; i++)
        file >> (obst_frequency_t &) frequency_[i];
      file.close();
    }
  }


template <class type_t>
optimal_binary_search_tree_t<type_t>::~optimal_binary_search_tree_t(void)
{}


template <class type_t>
void optimal_binary_search_tree_t<type_t>::solve(void)
{
  for(obst_inx_t i = 0; i < keys_.size(); i++)
    costs_(i, i) = frequency_[i];
 
  for(obst_inx_t L=2; L <= keys_.size(); L++)
  {
    const obst_inx_t limit = keys_.size() - L + 1;
    for(obst_inx_t i = 0; i <= limit; i++)
    {
      obst_inx_t j = i + L - 1;
      costs_(i, j) = std::numeric_limits<obst_frequency_t>::infinity();
      for(obst_inx_t r = i; r <= j; r++)
      {
        obst_frequency_t c = ((r > i) ? costs_(i, r - 1) : 0) +
                ((r < j) ? costs_(r + 1, j) : 0) +
                sum(i, j);
        if(c < costs_(i, j))
          costs_(i, j) = c;
      }
    }
  }
  std::cout << costs_ << std::endl;
}


template <class type_t>
obst_frequency_t optimal_binary_search_tree_t<type_t>::sum(obst_inx_t lower_limit, obst_inx_t upper_limit) const
{
  obst_frequency_t aux = 0;
  for (obst_inx_t k = lower_limit; k <= upper_limit; k++)
     aux += frequency_[k];
  return(aux);
}
