//Sample provided by Fabio Galuppo
//February 2017
//http://www.simplycpp.com

#ifndef BST_NODE_HPP
#define BST_NODE_HPP

template<typename T>
struct bst_node
{
	explicit bst_node(const T& value) :
		value(value),
		left(nullptr),
		right(nullptr) {}
	T value;
	bst_node<T>* left;
	bst_node<T>* right;

	bool operator==(const T& val) const
	{
		return value == val;
	}

	bool operator!=(const T& val) const
	{
		return value != val;
	}

	bool operator==(const bst_node<T>& that) const
	{
		return value == that.value && left == that.left && right == that.left;
	}

	bool operator!=(const bst_node<T>& that) const
	{
		return !(*this == that);
	}
};

#endif /* BST_NODE_HPP */