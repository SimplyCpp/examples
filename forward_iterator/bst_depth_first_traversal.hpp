//Sample provided by Fabio Galuppo
//February 2017
//http://www.simplycpp.com

#ifndef BST_DEPTH_FIRST_TRAVERSAL_HPP
#define BST_DEPTH_FIRST_TRAVERSAL_HPP

#include "bst_node.hpp"

#include <iterator>
#include <stack>

template<typename T>
struct bst_depth_search_travesal final : 
	public std::iterator<std::forward_iterator_tag, bst_node<T>>
{
	bst_depth_search_travesal()
	{
	}
	
	bst_depth_search_travesal(const bst_node<T>& root)
	{
		S.push(const_cast<bst_node<T>*>(&root));
	}

	bst_depth_search_travesal(const bst_depth_search_travesal<T>& that)
	{
		S = that.S;
	}

	bst_depth_search_travesal<T>& operator=(const bst_depth_search_travesal<T>& that)
	{
		if (that != *this)
		{
			S = that.S;
		}
		return *this;
	}

	~bst_depth_search_travesal()
	{
	}

	bool operator==(const bst_depth_search_travesal<T>& that) const
	{
		return S == that.S;
	}

	bool operator!=(const bst_depth_search_travesal<T>& that) const
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

	bst_depth_search_travesal<T>& operator++()
	{
		next();
		return *this;
	}

	bst_depth_search_travesal<T> operator++(int)
	{
		bst_depth_search_travesal<T> temp(*this);
		next();
		return temp;
	}	

private:
	bst_node<T>* value() const
	{
		return S.top();
	}

	void next()
	{
		if (!S.empty())
		{
			bst_node<T>* ptr = S.top();
			S.pop();
			if (ptr->right != nullptr)
				S.push(ptr->right);
			if (ptr->left != nullptr)
				S.push(ptr->left);
		}
	}

	std::stack<bst_node<T>*> S;
};

template<typename T>
struct bst_dfs_wrapper
{
	bst_dfs_wrapper(const bst_node<T>& root) : root(root) {}
	const bst_node<T>& root;
};

template<typename T>
inline bst_dfs_wrapper<T> dfs(const bst_node<T>& root)
{
	return bst_dfs_wrapper<T>(root);
}

template<typename T>
inline bst_depth_search_travesal<T> begin(const bst_dfs_wrapper<T>& wrapper)
{
	return bst_depth_search_travesal<T>(wrapper.root);
}

template<typename T>
inline bst_depth_search_travesal<T> end(const bst_dfs_wrapper<T>&)
{
	static bst_depth_search_travesal<T> instance;
	return instance;
}

#endif /* BST_DEPTH_FIRST_TRAVERSAL_HPP */