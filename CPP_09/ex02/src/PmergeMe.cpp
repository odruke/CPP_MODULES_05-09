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
_inputList(),
_inputDeque(),
_nElements(0),
_listDuration(0),
_dequeDuration(0) {}

PmergeMe::PmergeMe(int const& size, char** const& input)
{
	if (!_parseInput(size, input))
		throw ERROR_EXCPT("Invalid input\nUsage: ./PmergeMe 3 5 9 7 4...");

	this->_printBefore();

	this->_nElements = this->_inputList.size();
	this->_sortedSolution.sort();
}

PmergeMe::PmergeMe(PmergeMe const& copy) :
_inputList(copy._inputList),
_inputDeque(copy._inputDeque),
_nElements(copy._nElements),
_listDuration(copy._listDuration),
_dequeDuration(copy._dequeDuration) {}


PmergeMe::~PmergeMe() {}

/*========================= ASSIGN OPERATOR =============================================*/

PmergeMe&	PmergeMe::operator=(PmergeMe const& other)
{
	if (this == &other)
		return *this;

	this->_inputList = other._inputList;
	this->_inputDeque = other._inputDeque;
	this->_nElements = other._nElements;
	this->_listDuration = other._listDuration;
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
		this->_inputList.push_back(number);
		this->_inputDeque.push_back(number);
		this->_sortedSolution.push_back(number);
	}
	return true;
}

void	PmergeMe::_printBefore(void)
{
	std::cout << "Before: ";
	for (std::list<int>::iterator it = this->_inputList.begin(); it != this->_inputList.end(); it++)
	{
		std::cout << *it;
        std::list<int>::const_iterator next = it;
        ++next;
        if (next != this->_inputList.end())
            std::cout << ' ';
	}
	std::cout << std::endl;
}

void	PmergeMe::_printAfter()
{
	std::cout << "After: ";
	for (std::list<int>::iterator it = this->_inputList.begin(); it != this->_inputList.end(); it++)
	{
		std::cout << *it;
		std::list<int>::iterator next = it;
		++next;
		if (next != this->_inputList.end())
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

std::list<int>	PmergeMe::_sortList(std::list<int>& input)
{
	size_t size = input.size();
	if (input.size() <= 1)
		return input;

	bool	isOdd = (size % 2 != 0);
	int		extraItem;
	if (isOdd)
	{
		extraItem = input.back();
		input.pop_back();
	}

	//create pairs inside a pair list
	std::list<std::pair<int,int> >	pairs;
	if (!insertPair(pairs, input))
		throw(ERROR_EXCPT("Raw input size does not match"));

	//sort pairs of pair list
	sortPair(pairs);

	//create main and pend lists
	std::list<int>	mainList, pendList;

	makeMain(pairs, mainList);
	makePend(pairs, pendList);

	//recursion call with the new main list
	mainList = this->_sortList(mainList);

	//insert pend into main
	this->_insertListJacobsthall(mainList, pendList);

	//if extra insert extra
	if (isOdd)
		insertValue(mainList, extraItem);

	//sorted list is in main now


	return mainList;

}

void	PmergeMe::_insertListJacobsthall(std::list<int>& mainList, std::list<int>& pendList)
{
	if (pendList.empty())
		return;

	//create secuence based on list size
	size_t jacob[32];
	size_t jacobSize = createSecuence(jacob, pendList);

	size_t prevJacobIndex = 0;

	for (size_t i = 0; i < jacobSize; i++)
	{
		size_t currentJacobIndex = jacob[i];
		if (currentJacobIndex > pendList.size())
			currentJacobIndex = pendList.size();

		for (size_t blockIdx = currentJacobIndex; blockIdx > prevJacobIndex; --blockIdx)
		{
			std::list<int>::iterator it = pendList.begin();
			std::advance(it, blockIdx -1);

			insertValue(mainList, *it);
		}

		prevJacobIndex = currentJacobIndex;

		if (currentJacobIndex == pendList.size())
			break;
	}

}

std::deque<int>	PmergeMe::_sortDeque(std::deque<int>& input)
{
	size_t size = input.size();
	if (input.size() <= 1)
		return input;

	bool	isOdd = (size % 2 != 0);
	int		extraItem;
	if (isOdd)
	{
		extraItem = input.back();
		input.pop_back();
	}

	std::deque<std::pair<int,int> >	pairs;
	if (!insertPair(pairs, input))
		throw(ERROR_EXCPT("Raw input size does not match"));

	sortPair(pairs);

	std::deque<int>	mainList, pendList;

	makeMain(pairs, mainList);
	makePend(pairs, pendList);

	mainList = this->_sortDeque(mainList);

	this->_insertDequeJacobsthall(mainList, pendList);

	if (isOdd)
		insertValue(mainList, extraItem);

	return mainList;
}

void	PmergeMe::_insertDequeJacobsthall(std::deque<int>& mainList, std::deque<int>& pendList)
{
	if (pendList.empty())
		return;

	//create secuence based on list size
	size_t jacob[32];
	size_t jacobSize = createSecuence(jacob, pendList);

	size_t prevJacobIndex = 0;

	for (size_t i = 0; i < jacobSize; i++)
	{
		size_t currentJacobIndex = jacob[i];
		if (currentJacobIndex > pendList.size())
			currentJacobIndex = pendList.size();

		for (size_t blockIdx = currentJacobIndex; blockIdx > prevJacobIndex; --blockIdx)
		{
			int value = pendList[blockIdx - 1];
			insertValue(mainList, value);
		}

		prevJacobIndex = currentJacobIndex;

		if (currentJacobIndex == pendList.size())
			break;
	}

}

bool	PmergeMe::_compareLists(void)
{

	std::list<int>::iterator itList = this->_inputList.begin();
	std::deque<int>::iterator itDeque = this->_inputDeque.begin();

	while (itList != this->_inputList.end() && itDeque != this->_inputDeque.end())
	{
		if (*itList != *itDeque)
			return false;

		itList++;
		itDeque++;
	}

	if (this->_inputList != this->_sortedSolution)
		return false;
	return true;

}


/*======================= PUBLIC FUNCTIONS =============================================*/

void	PmergeMe::sortElements()
{
	double startTimer, endTimer;

	startTimer = nowMs();
	this->_inputList = this->_sortList(this->_inputList);
	endTimer = nowMs();
	this->_listDuration = endTimer - startTimer;


	startTimer = nowMs();
	this->_inputDeque = this->_sortDeque(this->_inputDeque);
	endTimer = nowMs();
	this->_dequeDuration = endTimer - startTimer;

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
