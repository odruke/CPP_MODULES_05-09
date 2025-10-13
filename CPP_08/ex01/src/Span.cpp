#include "Span.hpp"



/* ========== Constructors and destructor ==============*/
Span::Span()
{
	this->_numbers.reserve(2);
}

Span::Span(unsigned int const& maxN) : _maxN(maxN)
{
	this->_numbers.reserve(this->_maxN);
}

Span::Span(Span const& copy) : _maxN(copy._maxN)
{
	this->_numbers.reserve(this->_maxN);
}

Span::~Span() {}

/* ========== Member functions ==============*/
void	Span::addNumber(int const& number)
{
	if (this->_numbers.size() == this->_maxN)
		throw ContainerIsFull();

	this->_numbers.push_back(number);
}

size_t	Span::shortestSpan(void)
{
	if (this->_numbers.size() < 2)
		throw NotEnoughMembers();

	std::vector<int> sorted = this->_numbers;
	std::sort(sorted.begin(), sorted.end());
	size_t	shortest = SIZE_MAX;
	for (auto it = sorted.begin(); it != (sorted.end() - 1); it++)
	{
        size_t diff = static_cast<size_t>(*(it + 1) - *it);
        if (diff < shortest)
            shortest = diff;
	}
	return shortest;
}

size_t Span::longestSpan(void)
{
	if (this->_numbers.size() < 2)
		throw NotEnoughMembers();

	std::vector<int> sorted = this->_numbers;
	std::sort(sorted.begin(), sorted.end());

	int first = sorted.front();
	int	last = sorted.back();

	return static_cast<size_t>(last - first);
}

/* ========== Getters ==============*/
size_t	Span::getMaxCapacity(void) const
{
	return this->_maxN;
}

size_t	Span::getNumberOfElements(void) const
{
	return this->_numbers.size();
}

int	Span::getElement(size_t pos)
{
	if (pos > this->_maxN)
		throw std::out_of_range("Position out of range");
	return this->_numbers[pos];
}

/* ========== Overload operators ==============*/
Span&	Span::operator=(Span const& other)
{
	if (this == &other)
		return *this;
	this->_maxN = other._maxN;
	this->_numbers = other._numbers;
	return *this;
}

/* ========== Exceptions ==============*/
const char*	Span::ContainerIsFull::what() const throw()
{
	return "Container is already at max capacity";
}

const char*	Span::NotEnoughMembers::what() const throw()
{
	return "Not enough members to calculate";
}
