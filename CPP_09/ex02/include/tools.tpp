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


template< typename S, size_t N>
size_t	createSecuence(size_t (&jacob)[N], S const& pendContainer)//TODO create visualization of this
{
	size_t limit = pendContainer.size();
	size_t i = 0;

	if (N == 0 || limit == 0)
		return i;

	jacob[i++] = 1;
	if (i < N && 1 < limit)
		jacob[i++] = 3;

	while (i < limit)
	{
		size_t n = jacob[i - 1] + 2 * jacob[i - 2];
		if (i >= limit)
			break;
		jacob[i++] = n;
	}

	return i;
}

template< typename S>
typename S::iterator	binarySearch(S & container, int const& value)//TODO create visual explanation
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
