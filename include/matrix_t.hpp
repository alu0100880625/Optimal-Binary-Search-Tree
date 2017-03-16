#pragma once
#include <iostream>

typedef int matrix_inx_t;

template <class type_t>
class matrix_t
{
  private: 
    type_t* values_;
    matrix_inx_t rows_;
    matrix_inx_t columns_;
  public:
    matrix_t(void);
    matrix_t(matrix_inx_t rows, matrix_inx_t columns);
    matrix_t(const matrix_t &matrix);
    ~matrix_t(void);
    
    matrix_inx_t get_rows(void) const;
    matrix_inx_t get_columns(void) const;
    
    type_t get(matrix_inx_t row, matrix_inx_t column) const;
    void set(matrix_inx_t row, matrix_inx_t column, const type_t &value);
    type_t& get(matrix_inx_t row, matrix_inx_t column);
    
    type_t operator()(matrix_inx_t row, matrix_inx_t column) const;
    type_t& operator()(matrix_inx_t row, matrix_inx_t column);
    
    std::ostream& write(std::ostream &os) const;
    std::istream& read(std::istream &is);
    
    inline friend std::ostream& operator<<(std::ostream &os, const matrix_t<type_t> &matrix)
    {
      return(matrix.write(os));
    }
    
    inline friend std::istream& operator>>(std::istream &is, matrix_t<type_t> &matrix)
    {
      return(matrix.read(is));
    }
    
    void resize(matrix_inx_t rows, matrix_inx_t columns);
    private:
      matrix_inx_t get_pos(matrix_inx_t row, matrix_inx_t column) const;
      void create(void);
      void destroy(void);
};


template <class type_t>
matrix_t<type_t>::matrix_t(void):
  values_(nullptr),
  rows_(0),
  columns_(0)
  {}

  
template <class type_t>
matrix_t<type_t>::matrix_t(matrix_inx_t rows, matrix_inx_t columns):
  values_(nullptr),
  rows_(rows),
  columns_(columns)
  {
    create();
  }

  
template <class type_t>
matrix_t<type_t>::matrix_t(const matrix_t &matrix):
  values_(nullptr),
  rows_(matrix.get_rows()),
  columns_(matrix.get_columns())
  {
    create();
    for(matrix_inx_t i = 0; i < rows_; i++)
      for(matrix_inx_t j = 0; j < columns_; j++)
        this(i, j) = matrix(i, j);
  }

 
template <class type_t>
matrix_t<type_t>::~matrix_t(void)
{
  destroy();
  rows_ = columns_ = 0;
}


template <class type_t>
matrix_inx_t matrix_t<type_t>::get_rows(void) const
{
  return(rows_);
}


template <class type_t>
matrix_inx_t matrix_t<type_t>::get_columns(void) const
{
  return(columns_);
}


template <class type_t>
type_t matrix_t<type_t>::get(matrix_inx_t row, matrix_inx_t column) const
{
  return(values_[get_pos(row, column)]);
}


template <class type_t>
void matrix_t<type_t>::set(matrix_inx_t row, matrix_inx_t column, const type_t &value)
{
  values_[get_pos(row, column)] = value;
}


template <class type_t>
type_t& matrix_t<type_t>::get(matrix_inx_t row, matrix_inx_t column)
{
  return(values_[get_pos(row, column)]);
}


template <class type_t>
type_t matrix_t<type_t>::operator()(matrix_inx_t row, matrix_inx_t column) const
{
  return(get(row, column));
}


template <class type_t>
type_t& matrix_t<type_t>::operator()(matrix_inx_t row, matrix_inx_t column)
{
  return(get(row, column));
}


template <class type_t>
std::ostream& matrix_t<type_t>::write(std::ostream &os) const
{
  os << rows_ << std::endl;
  os << columns_ << std::endl;
  for(matrix_inx_t i = 0; i < rows_; i++)
  {
    for(matrix_inx_t j = 0; j < columns_; j++)
      os << get(i, j) << " ";
    os << std::endl;
  }
  return(os);
}


template <class type_t>
std::istream& matrix_t<type_t>::read(std::istream &is)
{
  destroy();
  is >> (matrix_inx_t &) rows_ >> (matrix_inx_t &) columns_;
  create();
  for(matrix_inx_t i = 0; i < rows_; i++)
    for(matrix_inx_t j = 0; j < columns_; j++)
      is >> get(i, j);
  return(is);
}


template <class type_t>
void matrix_t<type_t>::resize(matrix_inx_t rows, matrix_inx_t columns)
{
  destroy();
  rows_ = rows;
  columns_ = columns;
  create();
}


template <class type_t>
matrix_inx_t matrix_t<type_t>::get_pos(matrix_inx_t row, matrix_inx_t column) const
{
  return(get_columns() * row + column);
}


template <class type_t>
void matrix_t<type_t>::create(void)
{
   values_ = new type_t[rows_ * columns_];
}


template <class type_t>
void matrix_t<type_t>::destroy(void)
{
  if(values_ != nullptr)
  {
    delete [] values_;
    values_ = nullptr;
  }
}