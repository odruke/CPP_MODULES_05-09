#include <iostream>
#include "colors.hpp"
#include "iter.hpp"


/*============== helper print function, also a template! =============*/
template<typename T_array>
void	printArray(T_array const& array, std::string const& arrayName)
{
	for (size_t i = 0; i < ARRAY_SIZE(array); i++)
	{
		std::cout << "Element n"<< YELLOW << i << RESET
		<< " of " << arrayName << ": " << GREEN << array[i]
		<< RESET << std::endl;
	}
	std::cout << std::endl;
}

/*============== funtions to pass by reference (yes, they are highly unsafe)=============*/
void	ft_toupper(char &c) { c -= ('a' - 'A'); }

void	ft_increment(int &i) { i += 1; }

void	ft_shout(std::string &string) {string.append("!"); }

template<typename T>
void	printAnything(T const& anything) {std::cout << anything << std::endl;}


int	main()
{
	char		charArray[] = {'a', 'b', 'c'};
	int			intArray[] = {1, 2, 3};
	std::string	stringArray[] = {"this", "is", "a", "string"};

	printArray(charArray, "charArray");
	printArray(intArray, "intArray");
	printArray(stringArray, "stringArray");
	std::cout << std::endl;


/*============== tests =============*/
	std::cout << YELLOW << "\n============== test 1: array of char in lowercase to uppercase ============= \n" << RESET << std::endl;
	::iter(charArray, ARRAY_SIZE(charArray), ft_toupper);
	printArray(charArray, "charArray");

	std::cout << YELLOW << "\n============== test 2: array of int incremented by 1 ============= \n" << RESET << std::endl;
	::iter(intArray, ARRAY_SIZE(intArray), ft_increment);
	printArray(intArray, "intArray");

	std::cout << YELLOW << "\n============== test 3: array of string now screams! ============= \n" << RESET << std::endl;
	::iter(stringArray, ARRAY_SIZE(stringArray), ft_shout);
	printArray(stringArray, "stringArray");

	std::cout << YELLOW << "\n============== test 4:  using a template function with const argument ============= \n" << RESET << std::endl;
	::iter(charArray, ARRAY_SIZE(charArray), printAnything< char >);//Template functions must be instanciated!!
}
