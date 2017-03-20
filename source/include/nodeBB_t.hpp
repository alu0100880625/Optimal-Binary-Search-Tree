#pragma once
#include <iostream>

template<class Base_t>
class nodeBB_t
{
	private:
		nodeBB_t<Base_t>* left_;
		nodeBB_t<Base_t>* right_;
		Base_t data_;
	public:
		nodeBB_t(const Base_t &element);
		~nodeBB_t(void);

		void set_left(nodeBB_t<Base_t>* node);
		void set_right(nodeBB_t<Base_t>* node);
		void set_data(const Base_t &element);
		nodeBB_t<Base_t>* & get_left(void);
		nodeBB_t<Base_t>* & get_right(void);
		Base_t get_data(void) const;

		bool hoja(void) const;

		std::ostream& view(std::ostream &os) const;

		inline friend std::ostream& operator<<(std::ostream &os, nodeBB_t<Base_t>* node)
		{
			return(node->view(os));
		}

		inline friend std::ostream& operator<<(std::ostream &os, const nodeBB_t<Base_t> &node)
		{
			return(node.view(os));
		}
};

template<class Base_t>
nodeBB_t<Base_t>::nodeBB_t(const Base_t &element):
	left_(nullptr),
	right_(nullptr),
	data_(element)
	{}

template<class Base_t>
nodeBB_t<Base_t>::~nodeBB_t(void)
{}

template<class Base_t>
void nodeBB_t<Base_t>::set_left(nodeBB_t<Base_t>* node)
{
	left_ = node;
}

template<class Base_t>
void nodeBB_t<Base_t>::set_right(nodeBB_t<Base_t>* node)
{
	right_ = node;
}

template<class Base_t>
void nodeBB_t<Base_t>::set_data(const Base_t &element)
{
	data_ = element;
}

template<class Base_t>
nodeBB_t<Base_t>* & nodeBB_t<Base_t>::get_left(void)
{
	return(left_);
}

template<class Base_t>
nodeBB_t<Base_t>* & nodeBB_t<Base_t>::get_right(void)
{
	return(right_);
}

template<class Base_t>
Base_t nodeBB_t<Base_t>::get_data(void) const
{
	return(data_);
}

template<class Base_t>
bool nodeBB_t<Base_t>::hoja(void) const
{
	return(left_ == right_);
}

template<class Base_t>
std::ostream& nodeBB_t<Base_t>::view(std::ostream &os) const
{
	os << data_;
	return(os);
}
