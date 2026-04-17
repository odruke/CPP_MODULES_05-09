#pragma once

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include "colors.hpp"
#include "tools.tpp"

#ifndef DEBUG
# define DEBUG 0
#endif

#define ERROR_EXCPT(msg) errorExcept(__FILE__, __LINE__, msg)

template< typename C >
void	sortPair(C& container);

class PmergeMe
{
private:

	std::string	_rawInput;
	std::list<std::pair<int,int> >	_list;
	std::deque<std::pair<int,int> >	_deque;

	bool	_parseInput(int const& size, char** const& input);

public:
	PmergeMe();
	PmergeMe(int const& size, char** const& input);
	PmergeMe(PmergeMe const& copy);
	PmergeMe&	operator=(PmergeMe const& other);
	~PmergeMe();


	//public funcions
	void	sortList();
	void	sortDeque();

		class errorExcept : public std::exception
		{
			private:
				std::string	_msg;

			public:
				errorExcept(std::string const& file, int line, std::string msg);
				virtual ~errorExcept() throw();
				virtual const char* what() const throw();

		};
};

