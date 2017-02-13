//Sample provided by Fabio Galuppo
//February 2017
//http://www.simplycpp.com

#ifndef BST_BREADTH_FIRST_TRAVERSAL_HPP
#define BST_BREADTH_FIRST_TRAVERSAL_HPP

#include "bst_node.hpp"

#include <iterator>
#include <queue>

template<typename T>
struct bst_breadth_search_travesal final :
	public std::iterator<std::forward_iterator_tag, bst_node<T>>
{
	bst_breadth_search_travesal()
	{
	}

	bst_breadth_search_travesal(const bst_node<T>& root)
	{
		Q.push(const_cast<bst_node<T>*>(&root));
	}

	bst_breadth_search_travesal(const bst_breadth_search_travesal<T>& that)
	{
		Q = that.Q;
	}

	bst_breadth_search_travesal<T>& operator=(const bst_breadth_search_travesal<T>& that)
	{
		if (that != *this)
		{
			Q = that.Q;
		}
		return *this;
	}

	~bst_breadth_search_travesal()
	{
	}

	bool operator==(const bst_breadth_search_travesal<T>& that) const
	{
		return Q == that.Q;
	}

	bool operator!=(const bst_breadth_search_travesal<T>& that) const
	{
		return !(*this == that);
	}

	bst_node<T>& operator*() const
	{
		return *value();
	}

	bst_node<T>* operator->() const
	{
		return value();
	}

	bst_breadth_search_travesal<T>& operator++()
	{
		next();
		return *this;
	}

	bst_breadth_search_travesal<T> operator++(int)
	{
		bst_breadth_search_travesal<T> temp(*this);
		next();
		return temp;
	}

private:
	bst_node<T>* value() const
	{
		return Q.front();
	}

	void next()
	{
		if (!Q.empty())
		{
			bst_node<T>* ptr = Q.front();
			Q.pop();
			if (ptr->left != nullptr)
				Q.push(ptr->left);
			if (ptr->right != nullptr)
				Q.push(ptr->right);
		}
	}

	std::queue<bst_node<T>*> Q;
};

template<typename T>
struct bst_bfs_wrapper
{
	bst_bfs_wrapper(const bst_node<T>& root) : root(root) {}
	const bst_node<T>& root;
};

template<typename T>
inline bst_bfs_wrapper<T> bfs(const bst_node<T>& root)
{
	return bst_bfs_wrapper<T>(root);
}

template<typename T>
inline bst_breadth_search_travesal<T> begin(const bst_bfs_wrapper<T>& wrapper)
{
	return bst_breadth_search_travesal<T>(wrapper.root);
}

template<typename T>
inline bst_breadth_search_travesal<T> end(const bst_bfs_wrapper<T>&)
{
	static bst_breadth_search_travesal<T> instance;
	return instance;
}

#endif /* BST_BREADTH_FIRST_TRAVERSAL_HPP */