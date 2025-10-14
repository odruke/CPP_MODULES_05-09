#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <algorithm>

template< typename T, typename container = std::deque< T > >
class MutantStack : public std::stack<T, container>
{
private:

public:
//canonic form
	MutantStack();
	MutantStack(MutantStack const& copy);
	MutantStack&	operator=(MutantStack const& other);
	~MutantStack();

//iterators

	typedef typename container::iterator iterator;
	typedef typename container::const_iterator const_iterator;
	typedef typename container::reverse_iterator reverse_iterator;
	typedef typename container::const_reverse_iterator const_reverse_iterator;

	iterator		begin();
	const_iterator	cbegin()const;//c++11

	iterator		end();
	const_iterator	cend()const;//c++11

	iterator		rbegin();
	const_iterator	crbegin()const;//c++11

	iterator		rend();
	const_iterator	crend()const;//c++11
};

# include "MutantStack.tpp"
#endif
