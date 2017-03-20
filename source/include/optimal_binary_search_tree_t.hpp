#pragma once
#include "matrix_t.hpp"
#include "vector_t.hpp"
#include "ABB_t.hpp"

#include <iomanip>
#include <fstream>
#include <cstring>
#include <limits>

#define _DEBUG_
#define COUT_PRECISION 2

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

    void solve_dynamic_programming(void);
    void solve_bottom_up(void);
    ABB_t<type_t> reconstruct(void) const;
    private:
      obst_frequency_t sum(obst_inx_t lower_limit, obst_inx_t upper_limit) const;
      void recursive_reconstruct(obst_inx_t row, obst_inx_t column, nodeBB_t<type_t>* &node) const;
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
void optimal_binary_search_tree_t<type_t>::solve_dynamic_programming(void)
{
  matrix_t<obst_frequency_t> sum_matrix(keys_.size(), keys_.size());
  for(obst_inx_t i = 0; i < keys_.size(); i++)
    for(obst_inx_t j = 0; j < keys_.size(); j++)
      sum_matrix(i, j) = std::numeric_limits<obst_frequency_t>::infinity();

  for(obst_inx_t i = 0; i < keys_.size(); i++)
    costs_(i, i) = frequency_[i];

  #ifdef _DEBUG_
    obst_inx_t numero_iteraciones = 0;
    std::cout.precision(COUT_PRECISION);
    std::cout << std::fixed;
    std::cout << costs_ << std::endl;
  #endif

  for(obst_inx_t L=2; L <= keys_.size(); L++)
  {
    const obst_inx_t limit = keys_.size() - L;
    for(obst_inx_t i = 0; i <= limit; i++)
    {
      obst_inx_t j = i + L - 1;
      costs_(i, j) = std::numeric_limits<obst_frequency_t>::infinity();
      for(obst_inx_t r = i; r <= j; r++)
      {
        obst_frequency_t c = ((r > i) ? costs_(i, r - 1) : 0) +
                ((r < j) ? costs_(r + 1, j) : 0);
        if(sum_matrix(i, j) == std::numeric_limits<obst_frequency_t>::infinity())
        {
          sum_matrix(i, j) = sum(i, j);
          numero_iteraciones += j - i;
        }
        c += sum_matrix(i, j);
        #ifdef _DEBUG_
          std::cout
          << "L: " << L << " hasta: " << keys_.size() << std::endl
          << "i: " << i << " hasta: " << limit << std::endl
          << "j: " << j << std::endl
          << "r: " << r << " hasta: " << j << std::endl
          << "suma: " << ((r > i) ? std::string("coste(" + std::to_string(i) + ", " + std::to_string(r - 1) + ")") : "0")
          << " + " << ((r < j) ? std::string("coste(" + std::to_string(r + 1) + ", " + std::to_string(j) + ")") : "0")
          << " + " << "suma(" << i << ", " << j << ") (" << sum(i, j) << ") = " << c << std::endl
          << "coste(" << i << ", " << j << ") = " << costs_(i, j) << std::endl;
        #endif

        if(c < costs_(i, j))
        {
          costs_(i, j) = c;

          #ifdef _DEBUG_
            std::cout << "coste(" << i << ", " << j << ") ahora vale: " << c << std::endl;
          #endif
        }
        #ifdef _DEBUG_
          std::cout << costs_ << std::endl;
          numero_iteraciones++;
        #endif
      }
    }
    #ifdef _DEBUG_
      std::cout << "Número de iteraciones: " << numero_iteraciones << std::endl;
    #endif
  }
}


template <class type_t>
void optimal_binary_search_tree_t<type_t>::solve_bottom_up(void)
{
  #ifdef _DEBUG_
    obst_inx_t numero_iteraciones = 0;
    std::cout.precision(COUT_PRECISION);
    std::cout << std::fixed;
    std::cout << costs_ << std::endl;
  #endif

  for(obst_inx_t size = 1; size <= keys_.size(); size++)
  {
    const obst_inx_t limit = keys_.size() - size;
    for(obst_inx_t i = 0; i <= limit; i++)
    {
      obst_inx_t j = i + size - 1;
      costs_(i, j) = std::numeric_limits<obst_frequency_t>::infinity();
      for(obst_inx_t r = i; r <= j; r++)
      {
        obst_frequency_t temporal = sum(i, j);
        if(r > i)
          temporal += costs_(i, r - 1);
        if(r < j)
          temporal += costs_(r + 1, j);

        #ifdef _DEBUG_
          std::cout
          << "size: " << size << " hasta: " << keys_.size() << std::endl
          << "i: " << i << " hasta: " << limit << std::endl
          << "j: " << j << std::endl
          << "r: " << r << " hasta: " << j << std::endl
          << "suma: " << ((r > i) ? std::string("coste(" + std::to_string(i) + ", " + std::to_string(r - 1) + ")") : "0")
          << " + " << ((r < j) ? std::string("coste(" + std::to_string(r + 1) + ", " + std::to_string(j) + ")") : "0")
          << " + " << "suma(" << i << ", " << j << ") (" << sum(i, j) << ") = " << temporal << std::endl
          << "coste(" << i << ", " << j << ") = " << costs_(i, j) << std::endl;
        #endif

        if(temporal < costs_(i, j))
        {
          costs_(i,j) = temporal;

          #ifdef _DEBUG_
            std::cout << "coste(" << i << ", " << j << ") ahora vale: " << temporal << std::endl;
          #endif
        }

        #ifdef _DEBUG_
          std::cout << costs_ << std::endl;
          numero_iteraciones += j - i + 1;
        #endif
      }
    }
  }
  std::cout<<numero_iteraciones<<std::endl;
}


template <class type_t>
ABB_t<type_t> optimal_binary_search_tree_t<type_t>::reconstruct(void) const
{
  ABB_t<type_t> order_tree;

  recursive_reconstruct(0, keys_.size() - 1, order_tree.get_root());
  return(order_tree);
}


template <class type_t>
void optimal_binary_search_tree_t<type_t>::recursive_reconstruct(obst_inx_t row, obst_inx_t column, nodeBB_t<type_t>* &node) const
{
  for(obst_inx_t r = row; r <= column; r++)
  {
    if(costs_(row, column) == ((r > row) ? costs_(row, r - 1) : 0) +
      ((r < column) ? costs_(r + 1, column) : 0) + sum(row, column))
    {
      node = new nodeBB_t<type_t>(keys_[r]);
      recursive_reconstruct(r + 1, column,node->get_right());
      recursive_reconstruct(row, r - 1,node->get_left());
    }
  }

}

template <class type_t>
obst_frequency_t optimal_binary_search_tree_t<type_t>::sum(obst_inx_t lower_limit, obst_inx_t upper_limit) const
{
  obst_frequency_t aux = 0;
  for (obst_inx_t i = lower_limit; i <= upper_limit; i++)
     aux += frequency_[i];
  return(aux);
}
