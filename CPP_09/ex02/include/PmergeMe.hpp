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

	std::list<int>	_rawInput;
	id_t		_nElements;
	int			_additionalToken;
	bool		_isOdd;

	//list containers
	std::list<std::pair<int,int> >	_list;
	std::list<int> 					_mainList;
	std::list<int> 					_pendList;
	double							_listDuration;

	//deque containers
	std::deque<std::pair<int,int> >	_deque;
	std::deque<int> 				_mainDeque;
	std::deque<int> 				_pendDeque;
	double							_dequeDuration;



	bool	_parseInput(int const& size, char** const& input);
	void	_printBefore();

	void	_sortList();
	void	_sortDeque();
	bool	_compareLists();
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

