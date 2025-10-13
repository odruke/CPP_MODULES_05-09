#include <iostream>
#include "colors.hpp"
#include "Span.hpp"
#include <ctime>
#include <cstdlib>
# define INT_MAX std::numeric_limits<int>::max()

int randomNumber(int max)
{
	static bool seeded = false;

	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	int sign = ((rand() % 2) == 1? +1 : -1);
	return (rand() % (max + 1)) * sign;
}

void	fillSpan(Span& span)
{
	try
	{
		for (size_t i = 0; i < span.getMaxCapacity(); i++)
			span.addNumber(randomNumber(INT_MAX - 1));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	printSpan(Span& span)
{
	size_t i;
	for (i = 0; i < span.getNumberOfElements(); i++)
	{
		std::cout << "nº " << MAGENTA << span.getElement(i) << RESET;
		if (i < span.getNumberOfElements() - 1)
			std::cout << ", ";
	}
	if (i == 0)
		std::cout << RED << "No numbers to show" << RESET;
	std::cout << ";" << std::endl;

}
int	main()
{
/*============== test 1: subject example =============*/
	std::cout << YELLOW << "============== test 1: subject example =============" << RESET << std::endl;
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		printSpan(sp);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

/*============== test 2: working with regular capaticy =============*/
	std::cout << YELLOW << "\n============== test 2: working with regular capacity =============" << RESET << std::endl;
	{
		Span sp;
		try
		{
			sp = Span(5);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		fillSpan(sp);
		std::cout << "max capacity is = "<< GREEN << sp.getMaxCapacity() << RESET << std::endl;
		printSpan(sp);
		try
		{
			std::cout << "Shortest span is : " << CYAN << sp.shortestSpan() << RESET << std::endl;
			std::cout << "Longest span is : " << BLUE << sp.longestSpan() << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

/*============== test 3: working with high capacity =============*/
	std::cout << YELLOW << "\n============== test 2: working with high capacity =============" << RESET << std::endl;
	{
		Span sp;
		try
		{
			sp = Span(50000);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		fillSpan(sp);
		std::cout << "max capacity is = "<< GREEN << sp.getMaxCapacity() << RESET << std::endl;
		// printSpan(sp);
		try
		{
			std::cout << "Shortest span is : " << CYAN << sp.shortestSpan() << RESET << std::endl;
			std::cout << "Longest span is : " << BLUE << sp.longestSpan() << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

	}


/*============== test 3: elements overflow =============*/
	std::cout << YELLOW << "\n============== test 3: elements overflow =============" << RESET << std::endl;
	{
		Span sp;
		try
		{
			sp = Span(2);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		try
		{
			sp.addNumber(1);
			sp.addNumber(2);
			sp.addNumber(3);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		std::cout << "max capacity is = "<< GREEN << sp.getMaxCapacity() << RESET << std::endl;
		printSpan(sp);
		try
		{
			std::cout << "Shortest span is : " << CYAN << sp.shortestSpan() << RESET << std::endl;
			std::cout << "Longest span is : " << BLUE << sp.longestSpan() << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}


/*============== test 4: no numbers stored or only 1 number stored =============*/
	std::cout << YELLOW << "\n============== test 4: no numbers stored or only 1 number stored =============" << RESET << std::endl;
	{
		Span sp;
		try
		{
			sp = Span(2);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << "max capacity is = "<< GREEN << sp.getMaxCapacity() << RESET << std::endl;
		printSpan(sp);
		try
		{
			std::cout << "Shortest span is : " << CYAN << sp.shortestSpan() << RESET << std::endl;
			std::cout << "Longest span is : " << BLUE << sp.longestSpan() << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << YELLOW << "adding one number" << RESET << std::endl;
		sp.addNumber(1);
		printSpan(sp);
		try
		{
			std::cout << "Longest span is : " << BLUE << sp.longestSpan() << RESET << std::endl;
			std::cout << "Shortest span is : " << CYAN << sp.shortestSpan() << RESET << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

/*============== test 5: adding numbers from a range =============*/
	std::cout << YELLOW << "\n============== test 5: adding numbers from a range =============" << RESET << std::endl;
	{
		Span sp;
		std::vector<int> range;
		try
		{
			sp = Span(5);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		sp.addNumber(4);
		std::cout << "content of " << GREEN << "sp:" << RESET << std::endl;
		printSpan(sp);
		range.push_back(1);
		range.push_back(2);
		range.push_back(3);
		try
		{
			sp.addNumber(range.begin(), range.end());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << "content of " << GREEN << "sp:" << RESET << std::endl;
		printSpan(sp);

	}


/*============== test 6: adding numbers from a range causes overflow =============*/
	std::cout << YELLOW << "\n============== test 6: adding numbers from a range causes overflow =============" << RESET << std::endl;
	{
		Span sp;
		std::vector<int> range;
		try
		{
			sp = Span(3);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		sp.addNumber(4);
		std::cout << "content of " << GREEN << "sp:" << RESET << std::endl;
		printSpan(sp);
		range.push_back(2);
		range.push_back(3);
		range.push_back(4);
		try
		{
			sp.addNumber(range.begin(), range.end());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << "content of " << GREEN << "sp:" << RESET << std::endl;
		printSpan(sp);

	}
	return 0;
}
