#include "PmergeMe.hpp"

template< typename C >
void	sortPair(C& container)
{
	for (typename C::iterator it = container.begin(); it != container.end(); it++)
	{
		if (it->first > it->second)
			std::swap(it->first, it->second);
	}
}
