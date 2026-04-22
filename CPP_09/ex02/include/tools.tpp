#include "PmergeMe.hpp"

template< typename P >
void	sortPair(P& container)
{
	for (typename P::iterator it = container.begin(); it != container.end(); it++)
	{
		if (it->first > it->second)
			std::swap(it->first, it->second);
	}
}


template< typename P, typename S >
bool	insertPair(P& container, S const& input)
{

	typename S::const_iterator it = input.begin();

	while (it != input.end())
	{
		typename S::const_iterator next = it;
		std::advance(next, 1);
		if (it == input.end() || next == input.end())
			return false;

		std::pair<int, int> token(*it, *next);
		container.push_back(token);
		std::advance(it, 2);
	}
	return true;
}

template< typename P, typename S >
void	makeMain(P& containerPairs, S& containerSingle)
{
	for (typename P::iterator it = containerPairs.begin(); it != containerPairs.end(); it++)
		containerSingle.push_back(it->second);
}

template< typename P, typename S >
void	makePend(P& containerPairs, S& containerSingle)
{
	for (typename P::iterator it = containerPairs.begin(); it != containerPairs.end(); it++)
		containerSingle.push_back(it->first);
}

template< typename S>
typename S::iterator	binarySearch(S & container, int const& value)
{
	typename S::iterator left = container.begin();
	typename S::iterator right = container.end();

	while (left != right)
	{
		typename S::iterator mid = left;
		int dist = std::distance(left, right);
		std::advance(mid, dist /2);
		if (*mid < value)
			left = ++mid;
		else
			right = mid;
	}
	return left;
}

template< typename S>
void	insertValue(S & container, int const& value)
{
	typename S::iterator pos = binarySearch(container, value);
	container.insert(pos, value);
}
