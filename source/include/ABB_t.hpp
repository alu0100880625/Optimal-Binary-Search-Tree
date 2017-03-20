#pragma once
#include <queue>
#include <cmath>
#include "nodeBB_t.hpp"

typedef unsigned int ABB_inx_t;

template<class Base_t>
class ABB_t
{
	private:
		nodeBB_t<Base_t>* inicio_;
	public:
		ABB_t(void);
		~ABB_t(void);

		nodeBB_t<Base_t>* & get_root(void);

		bool empty(void) const;

		void insert(const Base_t &x);

		nodeBB_t<Base_t>* search(const Base_t &x);

		void remove(const Base_t &x);

		const ABB_inx_t size(void) const;
		const ABB_inx_t height(void) const;

		std::ostream& view(std::ostream &os) const;

		inline friend std::ostream& operator<<(std::ostream &os, const ABB_t<Base_t> &x)
		{
			return(x.view(os));
		}
	private:
		const ABB_inx_t size_rama(nodeBB_t<Base_t>* x) const;
		const ABB_inx_t height_node(nodeBB_t<Base_t>* x) const;
		void remove_rama(nodeBB_t<Base_t>* &node, const Base_t &x);
		nodeBB_t<Base_t>* search_rama(nodeBB_t<Base_t>* node, const Base_t &x);
		void insert_rama(nodeBB_t<Base_t>* &node, const Base_t &x);
		void podar(nodeBB_t<Base_t>* &node);
};

template<class Base_t>
ABB_t<Base_t>::ABB_t(void):
	inicio_(nullptr)
	{}

template<class Base_t>
ABB_t<Base_t>::~ABB_t(void)
{
	podar(inicio_);
}


template<class Base_t>
nodeBB_t<Base_t>* & ABB_t<Base_t>::get_root(void)
{
	return(inicio_);
}


template<class Base_t>
void ABB_t<Base_t>::podar(nodeBB_t<Base_t>* &node)
{
	if(node == nullptr)
		return;
	podar(node->get_left());
	podar(node->get_right());
	delete node;
	node = nullptr;
}

template<class Base_t>
bool ABB_t<Base_t>::empty(void) const
{
	return(inicio_ == nullptr);
}

template<class Base_t>
void ABB_t<Base_t>::insert(const Base_t &x)
{
	insert_rama(inicio_,x);
}

template<class Base_t>
void ABB_t<Base_t>::insert_rama(nodeBB_t<Base_t>* &node, const Base_t &x)
{
	if(node == nullptr)
		node = new nodeBB_t<Base_t>(x);
	else
	{
		if(x < node->get_data())
			insert_rama(node->get_left(),x);
		else
			if(x > node->get_data())
				insert_rama(node->get_right(),x);
	}
}


template<class Base_t>
nodeBB_t<Base_t>* ABB_t<Base_t>::search(const Base_t &x)
{
	return(search_rama(inicio_,x));
}


template<class Base_t>
nodeBB_t<Base_t>* ABB_t<Base_t>::search_rama(nodeBB_t<Base_t>* node, const Base_t &x)
{
	if(node == nullptr)
		return(nullptr);
	if(x == node->get_data())
		return(node);
	if(x < node->get_data())
		return(search_rama(node->get_left(), x));
	return(search_rama(node->get_right(), x));
}


template<class Base_t>
void ABB_t<Base_t>::remove(const Base_t &x)
{
	remove_rama(inicio_,x);
}


template<class Base_t>
void ABB_t<Base_t>::remove_rama(nodeBB_t<Base_t>* &node, const Base_t &x)
{
	if(node == nullptr)
		return;
	if(x < node->get_data())
		remove_rama(node->get_left(), x);
	else
		if(x > node->get_data())
			remove_rama(node->get_right(), x);
		else
		{
			nodeBB_t<Base_t>* rm = node;
			if(node->get_right() == nullptr)
			{
				node = node->get_left();
				delete (rm);
			}
			else
				if(node->get_left() == nullptr)
				{
					node = node->get_right();
					delete (rm);
				}
				else
				{
					nodeBB_t<Base_t> *aux = (node->get_left());
					while(aux->get_right() != nullptr)
						aux = aux->get_right();

					Base_t data = aux->get_data();

					remove_rama(node->get_left(), aux->get_data());
					node->set_data(data);
				}
		}
}


template<class Base_t>
const ABB_inx_t ABB_t<Base_t>::size(void) const
{
	return(size_rama(inicio_));
}

template<class Base_t>
const ABB_inx_t ABB_t<Base_t>::size_rama(nodeBB_t<Base_t>* x) const
{
	if(x == nullptr)
		return(0);
	return(1 + size_rama(x->get_left()) + size_rama(x->get_right()));
}


template<class Base_t>
const ABB_inx_t ABB_t<Base_t>::height(void) const
{
	return(height_node(inicio_));
}


template<class Base_t>
const ABB_inx_t ABB_t<Base_t>::height_node(nodeBB_t<Base_t>* x) const
{
	if(x == nullptr)
		return(0);
	ABB_inx_t h_l = height_node(x->get_left()), h_r = height_node(x->get_right());
	if(h_l > h_r)
		return(++h_l);
	return(++h_r);
}

template<class Base_t>
std::ostream& ABB_t<Base_t>::view(std::ostream &os) const
{
	std::queue< nodeBB_t<Base_t>* > cola_nodos;
	std::queue<ABB_inx_t> cola_niveles;
	ABB_inx_t h = height(), lvl = 0;
	cola_nodos.push(inicio_);
	cola_niveles.push(1);
	//lvl=0;
	++h;

	while(lvl <= h && !cola_nodos.empty())
	{
		if(lvl + 1 == cola_niveles.front())
		{
			if(lvl == h)
				return(os);
			os << std::endl;
			os << "Nivel: " << ++lvl << std::endl;
			os << "\t";
			for(ABB_inx_t i = pow(2, h - lvl + 1) - 1; i > 0; --i)
				os << " ";
		}
		else
			for(ABB_inx_t i = pow(2, h - lvl + 2) - 1; i > 0; --i)
				os << " ";

		nodeBB_t<Base_t>* aux = cola_nodos.front();
		cola_nodos.pop();
		if(aux == nullptr)
		{
			cola_nodos.push(nullptr);
			cola_niveles.push(cola_niveles.front() + 1);
			cola_nodos.push(nullptr);
			cola_niveles.push(cola_niveles.front() + 1);
		}
		else
		{
			cola_nodos.push(aux->get_left());
			cola_niveles.push(cola_niveles.front() + 1);
			cola_nodos.push(aux->get_right());
			cola_niveles.push(cola_niveles.front() + 1);
		}
		//for(ABB_inx_t i = lvl; i <= h; ++i)
			//os << "\t";
		if(aux == nullptr)
			os << "-";
		else
			os << aux;
		//for(ABB_inx_t i = lvl; i <= h; ++i)
			//os << " ";
		//for(ABB_inx_t i = lvl ; i <= h; i++)
			//os << "  ";
		cola_niveles.pop();
	}
	return(os);
}
