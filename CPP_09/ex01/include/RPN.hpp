#pragma once

#include "colors.hpp"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <sstream>

#ifndef DEBUG
# define DEBUG 0
#endif

#define ERROR_EXCPT(msg) errorExcept(__FILE__, __LINE__, msg)

class RPN
{
	private:

		std::stack<int> _stack;

	//operations
		//add +
		//substract -
		//multiply *
		//division /

	public:
		RPN(std::string const& expression);
		RPN(RPN const& copy);
		RPN&	operator=(RPN const& other);

		~RPN();

		void	printSolution(void);

		class errorExcept : std::exception
		{
			private:
				std::string	_msg;

			public:
				errorExcept(std::string const& file, int line, std::string msg);
				virtual ~errorExcept() throw();
				virtual const char* what() const throw();

		};
};
