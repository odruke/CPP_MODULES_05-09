#include "colors.hpp"
#include "easyfind.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <stack>
#include <ctime>
#include <cstdlib>

// int randomNumber(int max)
// {
// 	static bool seeded = false;

// 	if (!seeded) {
// 		srand(time(NULL));
// 		seeded = true;
// 	}
// 	return rand() % (max + 1);
// }
template<typename T>
void	printContainer(T& container)
{
	typename T::iterator it = container.begin();
	while (it != container.end())
	{
		std::cout << "nº " << YELLOW << *it << RESET;
		it++;
		if (it != container.end())
			std::cout << ", ";
	}
	std::cout << ";" << std::endl;
}

int	main()
{
	/* easyfind won't work with this kind of containers since
	stack doesn't have an iterator, and map elements are
	pairs(key, value), not a pure integer therefore we can't compare them*/
	// std::map<std::string, size_t>	map;
	// std::stack<int>					stk;

	std::list<int>		lst;
	std::vector<int>	vctr;
	int i;

	for (i = 0; i < 10; i++)
	{
		lst.push_back(i);
		vctr.push_back(i);
	}
	printContainer(lst);
	printContainer(vctr);

	if (NOEXCEPT)
	{
	/*============== test 1: try and find no exception version =============*/
		std::cout << YELLOW << "============== test 1: try and find no exception version =============" << RESET << std::endl;
		{
			std::list<int>::iterator it = easyfind(lst, 5);
			if (it == lst.end())
				std::cerr << "number not found in list" << std::endl;
			else
				std::cout << GREEN << "Number: " << BLUE << *it << GREEN << " found in list!" << RESET << std::endl;
		}

		{
			std::vector<int>::iterator it = easyfind(vctr, 5);
			if (it == vctr.end())
				std::cerr << "number not found in vector" << std::endl;
			else
				std::cout << GREEN << "Number: " << BLUE << *it << GREEN << " found in vector!" << RESET << std::endl;
		}

	/*============== test 2: try and fail no exception version =============*/
		std::cout << YELLOW << "============== test 2: try and fail no exception version =============" << RESET << std::endl;
		{
			std::list<int>::iterator it = easyfind(lst, 42);
			if (it == lst.end())
				std::cerr << "number not found in list" << std::endl;
			else
				std::cout << GREEN << "Number: " << BLUE << *it << GREEN << " found in list!" << RESET << std::endl;
		}

		{
			std::vector<int>::iterator it = easyfind(vctr, 42);
			if (it == vctr.end())
				std::cerr << "number not found in vector" << std::endl;
			else
				std::cout << GREEN << "Number: " << BLUE << *it << GREEN << " found in vector!" << RESET << std::endl;
		}
	}
	else
	{
	/*============== test 1: try and find exception version =============*/
		std::cout << YELLOW << "============== test 1: try and find exception version =============" << RESET << std::endl;
		{
			try
			{
				std::list<int>::iterator it = easyfind(lst, 5);
				std::cout << GREEN << "Number: " << BLUE << *it << GREEN << " found in list!" << RESET << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		{
			try
			{
				std::vector<int>::iterator it = easyfind(vctr, 5);
				std::cout << GREEN << "Number: " << BLUE << *it << GREEN << " found in vector!" << RESET << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

	/*============== test 2: try and fail exception version =============*/
		std::cout << YELLOW << "============== test 2: try and fail exception version =============" << RESET << std::endl;
		{
			try
			{
				std::list<int>::iterator it = easyfind(lst, 25);
				std::cout << GREEN << "Number" << BLUE << *it << " found!" << RESET << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		{
			try
			{
				std::vector<int>::iterator it = easyfind(vctr, 32);
				std::cout << GREEN << "Number" << BLUE << *it << " found!" << RESET << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}


}
