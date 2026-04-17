#include "PmergeMe.hpp"

/*========================== CONSTRUCTORS AND DESTRUCTOR ==============================*/
PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(int const& size, char** const& input)
{
	if (!_parseInput(size, input))
		throw ERROR_EXCPT("Invalid input\nUsage: ./PmergeMe 3 5 9 7 4...");

}
PmergeMe::PmergeMe(PmergeMe const& copy)
{

}
PmergeMe::~PmergeMe()
{

}
/*========================= ASSIGN OPERATOR =============================================*/

PmergeMe&	PmergeMe::operator=(PmergeMe const& other)
{

}

/*======================== PRIVATE FUNCTIONS ============================================*/
bool	PmergeMe::_parseInput(int const& size, char** const& input)
{
	for (int i = 1; i < size; i++)
	{
		std::string token(input[i]);
		if (token.empty())
			return false;

		for (int n = 0; n < token.length(); n++)
			if (!std::isdigit(token[n]))
				return false;

		long long int number = std::stoll(token);
		if (number < 0 || number > INT_MAX)
			return false;

	}


	return true;
}


/*======================= PUBLIC FUNCTIONS =============================================*/

/*========================== EXCEPTIONS ==============================*/

PmergeMe::errorExcept::errorExcept(std::string const& file, int line, std::string msg)
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

PmergeMe::errorExcept::~errorExcept(void) throw() {}

const char* PmergeMe::errorExcept::what(void) const throw()
{
	return this->_msg.c_str();
}
