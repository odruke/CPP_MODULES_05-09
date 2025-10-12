#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <stdexcept>
#  ifndef NOEXCEPT
#   define NOEXCEPT 0
#  endif

	template<typename T>
	typename T::iterator	easyfind(T& container, int value);

# include "easyfind.tpp"

#endif
