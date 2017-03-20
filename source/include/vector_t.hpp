#pragma once
#include <iostream>

typedef int vector_inx_t;

template <class type_t>
class vector_t
{
  private:
    type_t* values_;
    vector_inx_t size_;
  public:
    vector_t(void);
    vector_t(vector_inx_t size);
    vector_t(const vector_t &vector);
    ~vector_t(void);
     
    vector_inx_t size(void) const;
    
    type_t get(vector_inx_t position) const;
    void set(vector_inx_t position, const type_t &value);
    type_t& get(vector_inx_t position);
    
    type_t operator[](vector_inx_t position) const;
    type_t& operator[](vector_inx_t position);
    
    std::ostream& write(std::ostream &os) const;
    std::istream& read(std::istream &is);
    
    inline friend std::ostream& operator<<(std::ostream &os, const vector_t<type_t> &vector)
    {
      return(vector.write(os));
    }
  
    inline friend std::istream& operator>>(std::istream &is, vector_t<type_t> &vector)
    {
     return(vector.read(is)); 
    }
    
    void resize(vector_inx_t size);
    
  private:
    void create(void);
    void destroy(void);
};


template <class type_t>
vector_t<type_t>::vector_t(void):
  values_(nullptr),
  size_(0)
  {}


template <class type_t>
vector_t<type_t>::vector_t(vector_inx_t size):
  values_(nullptr),
  size_(size)
  {
    create();
  }


template <class type_t>
vector_t<type_t>::vector_t(const vector_t &vector):
  values_(nullptr),
  size_(vector.size())
  {
    create();
    for(vector_inx_t i = 0; i < size_; i++)
      get(i) = vector[i];
  }


template <class type_t>
vector_t<type_t>::~vector_t(void)
{
  destroy();
  size_ = 0;
}


template <class type_t>
vector_inx_t vector_t<type_t>::size(void) const
{
  return(size_);
}


template <class type_t>
type_t vector_t<type_t>::get(vector_inx_t position) const
{
  return(values_[position]);
}


template <class type_t>
void vector_t<type_t>::set(vector_inx_t position, const type_t &value)
{
  values_[position] = value;
}


template <class type_t>
type_t& vector_t<type_t>::get(vector_inx_t position)
{
  return(values_[position]);
}


template <class type_t>
type_t vector_t<type_t>::operator[](vector_inx_t position) const
{
  return(get(position));
}


template <class type_t>
type_t& vector_t<type_t>::operator[](vector_inx_t position)
{
  return(get(position));
}


template <class type_t>
std::ostream& vector_t<type_t>::write(std::ostream &os) const
{
  os << size_ << std::endl;
  for(vector_inx_t i = 0; i < size_; i++)
    os << get(i) << " ";
  return(os);
}


template <class type_t>
std::istream& vector_t<type_t>::read(std::istream &is)
{
  destroy();
  is >> (vector_inx_t &) size_;
  create();
  for(vector_inx_t i = 0; i < size_; i++)
    is >> get(i);
  return(is);
}


template <class type_t>
void vector_t<type_t>::resize(vector_inx_t size)
{
  destroy();
  size_ = size;
  create();
}


template <class type_t>
void vector_t<type_t>::create(void)
{
  values_ = new type_t[size_];
}

template <class type_t>
void vector_t<type_t>::destroy(void)
{
  if(values_ != nullptr)
  {
    delete [] values_;
    values_ = nullptr;
  }
}