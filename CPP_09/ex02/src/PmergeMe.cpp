#include "PmergeMe.hpp"

static double nowMs()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return static_cast<double>(ts.tv_sec) * 1000.0
			+ static_cast<double>(ts.tv_nsec) / 1000000.0;
}

/*========================== CONSTRUCTORS AND DESTRUCTOR ==============================*/
PmergeMe::PmergeMe() :
_rawInput(),
_nElements(0),
_additionalToken(0),
_isOdd(false),
_list(),
_mainList(),
_pendList(),
_listDuration(0),
_deque(),
_mainDeque(),
_pendDeque(),
_dequeDuration(0) {}

PmergeMe::PmergeMe(int const& size, char** const& input)
{
	if (!_parseInput(size, input))
		throw ERROR_EXCPT("Invalid input\nUsage: ./PmergeMe 3 5 9 7 4...");
	this->_printBefore();
	this->_nElements = this->_rawInput.size();
}

PmergeMe::PmergeMe(PmergeMe const& copy) :
_rawInput(copy._rawInput),
_nElements(copy._nElements),
_additionalToken(copy._additionalToken),
_isOdd(copy._isOdd),
_list(copy._list),
_mainList(copy._mainList),
_pendList(copy._pendList),
_listDuration(copy._listDuration),
_deque(copy._deque),
_mainDeque(copy._mainDeque),
_pendDeque(copy._pendDeque),
_dequeDuration(copy._dequeDuration) {}


PmergeMe::~PmergeMe() {}

/*========================= ASSIGN OPERATOR =============================================*/

PmergeMe&	PmergeMe::operator=(PmergeMe const& other)
{
	if (this == &other)
		return *this;

	this->_rawInput = other._rawInput;
	this->_nElements = other._nElements;
	this->_additionalToken = other._additionalToken;
	this->_isOdd = other._isOdd;
	this->_list = other._list;
	this->_mainList = other._mainList;
	this->_pendList = other._pendList;
	this->_listDuration = other._listDuration;
	this->_deque = other._deque;
	this->_mainDeque = other._mainDeque;
	this->_pendDeque = other._pendDeque;
	this->_dequeDuration = other._dequeDuration;

	return *this;
}

/*======================== PRIVATE FUNCTIONS ============================================*/
bool	PmergeMe::_parseInput(int const& size, char** const& input)
{
	for (int i = 1; i < size; i++)
	{
		std::string token(input[i]);
		if (token.empty())
			return false;

		for (size_t n = 0; n < token.length(); n++)
			if (!std::isdigit(token[n]))
				return false;

		int number = std::atol(token.c_str());
		if (number < 0 || number > INT_MAX)
			return false;
		this->_rawInput.push_back(number);
	}
	return true;
}

void	PmergeMe::_printBefore(void)
{
	std::cout << "Before: ";
	for (std::list<int>::iterator it = this->_rawInput.begin(); it != this->_rawInput.end(); it++)
	{
		std::cout << *it;
        std::list<int>::const_iterator next = it;
        ++next;
        if (next != this->_rawInput.end())
            std::cout << ' ';
	}
	std::cout << std::endl;
}

void	PmergeMe::_printAfter()
{
	std::cout << "Before: ";
	for (std::list< std::pair<int, int> >::iterator it = this->_list.begin(); it != this->_list.end(); it++)
	{
		std::cout << it->first << ' ' << it->second;
		std::list< std::pair<int, int> >::iterator next = it;
		++next;
		if (next != this->_list.end())
			std::cout << ' ';
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of "
			<< this->_nElements
			<< " elements with std::list : "
			<< this->_listDuration
			<< "ms" << std::endl;

	std::cout << "Time to process a range of "
			<< this->_nElements
			<< " elements with std::deque : "
			<< this->_dequeDuration
			<< "ms" << std::endl;
}

void	PmergeMe::_sortList()
{
	double startTimer = nowMs();


	double endTimer = nowMs();
	this->_listDuration = endTimer - startTimer;
}

void	PmergeMe::_sortDeque()
{
	double startTimer = nowMs();


	double endTimer = nowMs();
	this->_dequeDuration = endTimer - startTimer;
}

bool	PmergeMe::_compareLists()
{
	std::list<std::pair<int, int> >::iterator itList = this->_list.begin();
	std::deque<std::pair<int, int> >::iterator itDeque = this->_deque.begin();

	while (itList != this->_list.end() && itDeque != this->_deque.end())
	{
		if (itList->first != itDeque->first)
			return false;
		if (itList->second != itDeque->second)
			return false;

		itList++;
		itDeque++;
	}
	return true;

}


/*======================= PUBLIC FUNCTIONS =============================================*/

void	PmergeMe::sortElements()
{
	this->_sortList();
	this->_sortDeque();
	if (!this->_compareLists())
		throw(ERROR_EXCPT("sorting failed, container lists do not match"));

	this->_printAfter();
}



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
