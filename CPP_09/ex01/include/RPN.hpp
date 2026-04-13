#pragma once

#include "colors.hpp"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <algorithm>

#ifndef DEBUG
# define DEBUG 0
#endif

#define ERROR_EXCPT(msg) errorExcept(__FILE__, __LINE__, msg)
#define ARRAY_SIZE(array)((int)(sizeof(array) / sizeof(array[0])))



class RPN
{
	public:
	class BigInt;

	private:

	std::stack<BigInt> _stack;
	std::string		_solution;

	//operations
	void	_add(void);
	void	_substract(void);
	void	_multiply(void);
	void	_divide(void);

	//process
	std::string	_processExpression(std::string const& expression);

	public:
		RPN();
		RPN(std::string const& expression);
		RPN(RPN const& copy);
		RPN&	operator=(RPN const& other);

		~RPN();

		void	printSolution(void);

		class BigInt
		{
			private:
				std::string	_num;
				bool		_isNegative;
				int		_compareAbs(std::string const& a, std::string const& b) const;
				std::string	_addAbs(std::string const& a, std::string const& b) const;
				std::string	_subAbs(std::string const& a, std::string const& b) const;
				std::string	_mulAbs(std::string const& a, std::string const& b) const;
				std::string	_divAbs(std::string const& a, std::string const& b) const;
				void		_normalize(void);
			public:
				BigInt(std::string const& num);
				BigInt(BigInt const& copy);
				BigInt&	operator=(BigInt const& other);
				~BigInt();

				std::string	getNum() const;

				BigInt	operator+(BigInt const& other);
				BigInt	operator-(BigInt const& other);
				BigInt	operator*(BigInt const& other);
				BigInt	operator/(BigInt const& other);

				bool	operator==(BigInt const& other) const;
				bool	operator!=(BigInt const& other) const;
				bool	operator<(BigInt const& other) const;
				bool	operator>(BigInt const& other) const;
				bool	operator>=(BigInt const& other) const;
				bool	operator<=(BigInt const& other) const;

		};

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

std::ostream&	operator<<(std::ostream &os, RPN::BigInt Num);
