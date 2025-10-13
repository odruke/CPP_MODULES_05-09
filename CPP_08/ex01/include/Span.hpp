#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <exception>
# include <stdexcept>
# include <limits>
# include <algorithm>

# define SIZE_MAX std::numeric_limits<size_t>::max()

class Span
{
private:
	std::vector<int>	_numbers;
	size_t				_maxN;
public:
//canonic form
	Span();
	Span(unsigned int const& maxN);
	Span(Span const& copy);
	Span&	operator=(Span const& other);
	~Span();

//getters
	size_t	getMaxCapacity() const;
	size_t	getNumberOfElements() const;
	int		getElement(size_t pos);

//member functions
	void	addNumber(int const& number);
	size_t	shortestSpan();
	size_t	longestSpan();

//exceptions

	class ContainerIsFull : public std::exception
	{
	public:
		virtual const char*	what() const throw();
	};

	class NotEnoughMembers : public std::exception
	{
	public:
		virtual const char*	what() const throw();
	};
};

#endif
