#include "RPN.hpp"

/*======================= CONSTRUCTOR AND DESTRUCTOR ============================*/

//1.constructor takes raw string
//2.parsing
//3.processing
//4.storing result

RPN::RPN(std::string const& expression)
{
	size_t badToken = expression.find_first_not_of("0123456789 -+*/");
	if ( badToken != std::string::npos)
	{
		char bad = expression.at(badToken);
		throw ERROR_EXCPT(std::string("bad token: ") + bad);
	}

	this->_solution = this->_processExpression(expression);

}

RPN::RPN(RPN const& copy) : _stack(copy._stack), _solution(copy._solution){}

RPN::~RPN(void) {}

/*======================== ASSING OPERATOR =============================================*/

RPN&	RPN::operator=(RPN const& other)
{
	if (this == &other)
		return *this;
	this->_stack = other._stack;
	this->_solution = other._solution;

	return *this;
}

/*========================= PRIVATE FUNCTIONS =====================================================*/

//OPERATORS
void	RPN::_add(void)//TODO check safeguard for max LONG INT operations
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	long long int	b = this->_stack.top();
	this->_stack.pop();
	long long int	a = this->_stack.top();
	this->_stack.pop();

	long long int result = a + b;
	this->_stack.push(result);
}

void	RPN::_substract(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	long long int	b = this->_stack.top();
	this->_stack.pop();
	long long int	a = this->_stack.top();
	this->_stack.pop();

	long long int result = a - b;
	this->_stack.push(result);
}

void	RPN::_multiply(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	long long int	b = this->_stack.top();
	this->_stack.pop();
	long long int	a = this->_stack.top();
	this->_stack.pop();

	long long int result = a * b;
	this->_stack.push(result);
}

void	RPN::_divide(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	long long int	b = this->_stack.top();
	this->_stack.pop();
	long long int	a = this->_stack.top();
	this->_stack.pop();

	long long int result = a / b;
	this->_stack.push(result);
}

//PROCESS
std::string	RPN::_processExpression(std::string const& expresssion)//pointer over function
{
	//1.add a token to the stack
	//first 2 token must be number, we can check stack size
	//after each number or operator must be space
	//if operator extract call operation function. We have to check stack size if not min 2 throw
	//operator function extracts 2 last tokens, operates, and stores result

	std::string operators = "+-*/";
	void	(RPN::*operation[operators.size()])() = {&RPN::_add, &RPN::_substract, &RPN::_multiply, &RPN::_divide};

	bool	expectedSpace = false;
	char	token = expresssion.at(0);
	for (size_t i = 0; i < expresssion.size(); i++)
	{
		token = expresssion.at(i);

		if (std::isdigit(token))
		{
			if (expectedSpace)
				throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

			int		num = token - '0';
			this->_stack.push(num);
			expectedSpace = true;
		}
		else if (token == ' ')
		{
			if (!expectedSpace)
				throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

			expectedSpace = false;
		}
		else
		{
			if (expectedSpace || operators.find(token) == std::string::npos)
				throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

			for (size_t j = 0; j < operators.size(); j++)
			{
				if (operators.at(j) == token)
				{
					(this->*operation[j])();
					break;
				}
			}

			expectedSpace = true;
		}
	}

	if (this->_stack.size() != 1)
		throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

	std::ostringstream oss;
	oss << this->_stack.top();

	return oss.str();

}

/*========================== PUBLIC FUNCTIONS =======================================================*/

void	RPN::printSolution(void)
{
	std::cout << this->_solution << std::endl;
}


/*======================== EXCEPTIONS =============================================*/

RPN::errorExcept::errorExcept(std::string const& file, int line, std::string msg)
{
	if (DEBUG)
	{
		std::ostringstream oss;
		oss << RED << "Error at: " << RESET
		<< file  << ":" << line << "\n"
		<< RED << msg;
		this->_msg = oss.str();
	}
	else
		this->_msg =  "Error";

}

RPN::errorExcept::~errorExcept(void) throw() {}

const char* RPN::errorExcept::what(void) const throw()
{
	return this->_msg.c_str();
}
