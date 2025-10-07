#include "ScalarConverter.hpp"
#include "colors.hpp"

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << ORANGE << "\nTEST 1:" << RESET << std::endl;
		ScalarConverter::convert("a");

		std::cout << ORANGE << "\nTEST 2:" << RESET << std::endl;
		ScalarConverter::convert("1");

		std::cout << ORANGE << "\nTEST 3:" << RESET << std::endl;
		ScalarConverter::convert("1.2f");

		std::cout << ORANGE << "\nTEST 4:" << RESET << std::endl;
		ScalarConverter::convert("1.2");

		std::cout << ORANGE << "\nTEST 5:" << RESET << std::endl;
		ScalarConverter::convert("patata");

		std::cout << ORANGE << "\nTEST 6:" << RESET << std::endl;
		ScalarConverter::convert(".2");

		std::cout << ORANGE << "\nTEST 7:" << RESET << std::endl;
		ScalarConverter::convert("1..3");

		std::cout << ORANGE << "\nTEST 8:" << RESET << std::endl;
		ScalarConverter::convert("1.2.3");

		std::cout << ORANGE << "\nTEST 9:" << RESET << std::endl;
		ScalarConverter::convert("1.a");

		std::cout << ORANGE << "\nTEST 10:" << RESET << std::endl;
		ScalarConverter::convert("1.f1");

	}
	else if (ac == 2)
		ScalarConverter::convert(av[1]);
	else
		std::cerr << "Too many arguments" << std::endl;
}
