#if NOEXCEPT
/* A more explicit function.
Retuns container.end() instead of throwing an error as the original std::find */
template<typename T>
typename T::iterator	easyfind(T& container, int value)
{
	typename T::iterator it = container.begin();
	typename T::iterator itn = container.end();
	while (it != itn)
	{
		if (*it == value)
			break ;
		it++;
	}
	return it;
}
#else
/* pure c++ version. Basically a wrap for the std::function
but with a different approach on error management */
template<typename T>
typename T::iterator	easyfind(T& container, int value)
{
	typename T::iterator	it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw std::out_of_range("Value not found");
	return it;
}
#endif
