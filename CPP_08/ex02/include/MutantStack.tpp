/* ========== Constructors and destructor ==============*/
template<typename T, typename container>
MutantStack<T, container>::MutantStack() : std::stack<T, container>() {}

template<typename T, typename container>
MutantStack<T, container>::MutantStack(MutantStack const& copy) : std::stack<T, container>(copy) {}

template<typename T, typename container>
MutantStack<T, container>::~MutantStack() {}

/* ========== iterators ==============*/
template<typename T, typename container>//		<-templates
typename MutantStack<T, container>::iterator//	<-return type, in c++11 we can replace for the keyword "auto"
MutantStack<T, container>::begin(void)//		<-scope and function declaration. The scope must also indicate the templates he's using
{
	return this->c.begin();
}

template<typename T, typename container>
typename MutantStack<T, container>::const_iterator
MutantStack<T, container>::cbegin(void) const
{
	return this->c.cbegin();
}

template<typename T, typename container>
typename MutantStack<T, container>::iterator
MutantStack<T, container>::end(void)
{
	return this->c.end();
}

template<typename T, typename container>
typename MutantStack<T, container>::const_iterator
MutantStack<T, container>::cend(void) const
{
	return this->c.cend();
}

template<typename T, typename container>
typename MutantStack<T, container>::iterator
MutantStack<T, container>::rbegin(void)
{
	return this->c.rbegin();
}

template<typename T, typename container>
typename MutantStack<T, container>::const_iterator
MutantStack<T, container>::crbegin(void) const
{
	return this->c.crbegin();
}

template<typename T, typename container>
typename MutantStack<T, container>::iterator
MutantStack<T, container>::rend(void)
{
	return this->c.rend();
}

template<typename T, typename container>
typename MutantStack<T, container>::const_iterator
MutantStack<T, container>::crend(void) const
{
	return this->c.crend();
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


