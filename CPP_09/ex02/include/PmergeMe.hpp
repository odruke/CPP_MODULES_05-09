#pragma once

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <time.h>
#include "colors.hpp"
#include "tools.tpp"

#ifndef DEBUG
# define DEBUG 0
#endif

#define ERROR_EXCPT(msg) errorExcept(__FILE__, __LINE__, msg)

/*=================== TEMPLATES ============================*/
template< typename P >
void	sortPair(P& container);

template< typename P, typename S >
bool	insertPair(P& container, S const& input);

template< typename P, typename S >
void	makePend(P& containerPairs, S& containerSingle);

template< typename P, typename S >
void	makeMain(P& containerPairs, S& containerSingle);

template< typename S>
typename S::iterator	binarySearch(S const& container, int const& value);

template< typename S>
void	insertValue(S & container, int const& value);

template< typename S, size_t N>
size_t	createSecuence(size_t (&jacob)[N], S const& pendContainer);

/*=============================================================*/

class PmergeMe
{
private:

	//containers
	std::list<int>	_inputList;
	std::deque<int>	_inputDeque;
	std::list<int>	_sortedSolution;

	//info variables
	id_t		_nElements;
	double		_listDuration;
	double		_dequeDuration;

	//sorting functions
	std::list<int>	_sortList(std::list<int>& input);
	void			_insertListJacobsthall(std::list<int>& mainList, std::list<int>& pendList);

	std::deque<int>	_sortDeque(std::deque<int>& input);
	void			_insertDequeJacobsthall(std::deque<int>& mainList, std::deque<int>& pendList);

	//helper funtions
	bool	_parseInput(int const& size, char** const& input);
	bool	_compareLists();
	void	_printBefore();
	void	_printAfter();

public:
	PmergeMe();
	PmergeMe(int const& size, char** const& input);
	PmergeMe(PmergeMe const& copy);
	PmergeMe&	operator=(PmergeMe const& other);
	~PmergeMe();


	//public funcions
	void	sortElements();

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

