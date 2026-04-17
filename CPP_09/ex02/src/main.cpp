#include "PmergeMe.hpp"
/*create a template class that will store the input in both deque and list containers.*/
int main(int ac, char **av)
{
	if (ac < 2)
	{
		if (DEBUG)
			std::cerr << "Usage: ./PmergeMe 3 4 6 3" << std::endl;
		else
			std::cerr << "Error" << std::endl;
	}

	try
	{
		PmergeMe myList(ac, av);
		myList.sortList();
		myList.sortDeque();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}
