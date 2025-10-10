#ifndef ITER_HPP
# define ITER_HPP

# define ARRAY_SIZE(array)((unsigned int)(sizeof(array) / sizeof(array[0])))

template< typename T, typename F >
void	iter(T* array, unsigned int const& size, F function)
{
	if (array == NULL || function == NULL)
		return;
	for (size_t i = 0; i < size; i++)
		function(array[i]);
}

/*This solution will only accept non const references for the argument
of the third parameter, so is a less flexible way to implement it, and
is specifically asked for the subject to be able to admit both const
and non const parameters*/

// template< typename T >
// void	iter(T* array, unsigned int const& size, void(*function)(T&))
// {
// 	if (array == NULL || function == NULL)
// 		return;
// 	for (size_t i = 0; i < size; i++)
// 		function(array[i]);
// }
#endif
