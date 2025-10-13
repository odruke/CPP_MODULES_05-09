/* ========== Constructors and destructor ==============*/
template<typename T, typename container>
MutantStack<T, container>::MutantStack() : std::stack<T, container>() {}

template<typename T, typename container>
MutantStack<T, container>::MutantStack(MutantStack const& copy) : std::stack<T, container>(copy) {}

template<typename T, typename container>
MutantStack<T, container>::~MutantStack() {}

/* ========== iterators ==============*/
template<typename T, typename container>
typename MutantStack<T, container>::iterator
MutantStack<T, container>::begin(void)
{
	return this->c.begin();
}

template<typename T, typename container>
typename MutantStack<T, container>::const_iterator
MutantStack<T, container>::begin(void) const
{
	return this->c.begin();
}

template<typename T, typename container>
typename MutantStack<T, container>::iterator
MutantStack<T, container>::end(void)
{
	return this->c.end();
}

template<typename T, typename container>
typename MutantStack<T, container>::const_iterator
MutantStack<T, container>::end(void) const
{
	return this->c.end();
}


/* ========== overload operator ==============*/
template<typename T, typename container>
MutantStack<T, container>&	MutantStack<T, container>::operator=(MutantStack const& other)
{
	if (this == &other)
		return *this;
	std::stack<T, container>::operator=(other);
	return *this;
}


