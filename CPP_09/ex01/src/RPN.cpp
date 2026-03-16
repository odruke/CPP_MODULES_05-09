#include "RPN.hpp"

/*======================= CONSTRUCTOR AND DESTRUCTOR ============================*/

//1.constructor takes raw string
//2.parsing
//3.processing
//4.storing result

/*======================== ASSING OPERATOR =============================================*/


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
		std::cout << "Error";

}

RPN::errorExcept::~errorExcept(void) throw() {}

const char* RPN::errorExcept::what(void) const throw()
{
	return this->_msg.c_str();
}
