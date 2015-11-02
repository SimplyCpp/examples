//Sample provided by Fabio Galuppo
//October 2015
//http://www.simplycpp.com

#include <iterator>
#include <functional>

//ForwardIterator Ref.: http://www.cplusplus.com/reference/iterator/ForwardIterator/

template <class Container, class UnaryPredicate>
struct forward_iterator_with_predicate;

template <class Container, class UnaryPredicate>
struct iterator_with_predicate final
{
	iterator_with_predicate(Container& cont, UnaryPredicate pred)
		: fiwp(cont, pred)
	{
		refresh();
	}
	
	//begin and end:
	forward_iterator_with_predicate<Container, UnaryPredicate> begin() const
	{
		forward_iterator_with_predicate<Container, UnaryPredicate> temp = fiwp;		
		temp.update_begin();
		return temp;
	}

	forward_iterator_with_predicate<Container, UnaryPredicate> end() const
	{
		return fiwp;
	}

	void refresh() { fiwp.update_end(); }

private:
	forward_iterator_with_predicate<Container, UnaryPredicate> fiwp;
};

template <class Container, class UnaryPredicate = std::function<bool(typename Container::value_type)>>
auto make_iterator_with_predicate(Container& cont, UnaryPredicate pred) -> iterator_with_predicate<Container, decltype(pred)>
{
	return iterator_with_predicate<Container, decltype(pred)>(cont, pred);
}

template <class Container, class UnaryPredicate = std::function<bool(typename Container::value_type)>>
auto begin(iterator_with_predicate<Container, UnaryPredicate>& iwp) -> decltype(iwp.begin())
{
	return iwp.begin();
}

template <class Container, class UnaryPredicate>
auto end(iterator_with_predicate<Container, UnaryPredicate> iwp) -> decltype(iwp.end())
{
	return iwp.end();
}

template <class Container, class UnaryPredicate>
struct forward_iterator_with_predicate final :
	public std::iterator<std::forward_iterator_tag, typename Container::value_type>
{
	using value_type = typename Container::value_type;

private:
	//constructor and destructor:
	explicit forward_iterator_with_predicate(Container& cont, UnaryPredicate pred) :
		cont(cont),
		pred(pred)
	{
	}

	friend struct iterator_with_predicate<Container, UnaryPredicate>;

public:
	//default-constructible
	forward_iterator_with_predicate() = delete;

	//copy-constructible
	forward_iterator_with_predicate(const forward_iterator_with_predicate& that) = default;

	//copy-assignable
	forward_iterator_with_predicate& operator=(const forward_iterator_with_predicate& that) = default;

	~forward_iterator_with_predicate() = default;

	//comparison:
	//comparable for inequality
	bool operator!=(const forward_iterator_with_predicate& that) const
	{
		return !(*this == that);
	}

	//comparable for equality
	bool operator==(const forward_iterator_with_predicate& that) const
	{
		return cont_first == that.cont_end;
	}

	//dereference:
	//dereferenceable
	value_type& operator*() const
	{
		return *cont_first;
	}

	//dereferenceable
	value_type* operator->() const
	{
		return cont_first;
	}

	//increment:
	//pre increment
	forward_iterator_with_predicate& operator++()
	{
		next();
		return *this;
	}

private:
	void update_end()
	{
		cont_end = cont.end();
	}

	void update_begin()
	{
		cont_first = cont.begin();		
		if (!pred(*cont_first)) //set begin position
			next();
	}

	void next()
	{
		while (++cont_first != cont_end)
		{
			if (pred(*cont_first))
				break;
		}
	}

	Container& cont;
	UnaryPredicate pred;
	typename Container::iterator cont_first, cont_end;
};
