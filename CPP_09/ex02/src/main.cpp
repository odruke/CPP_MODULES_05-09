#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		if (DEBUG)
			std::cerr << "Usage: ./PmergeMe 3 4 6 3" << std::endl;
		else
			std::cerr << "Error" << std::endl;

		return 1;
	}

	try
	{
		PmergeMe myList(ac, av);
		myList.sortElements();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
