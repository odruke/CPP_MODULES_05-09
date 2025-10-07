#include "ScalarConverter.hpp"
#include "colors.hpp"
#include <limits>
#include <cctype>

void	mainPrint(t_convertedValue value, e_type type)
{
	std::cout << CYAN << "char: " << RESET;
	if (!isprint(value.cVal) || type == UNKNOWN)
		std::cout << RED << "Non displayable" << RESET << std::endl;
	else
		std::cout << "'" << value.cVal << "'" << std::endl;

	std::cout << CYAN << "int: " << RESET;
	if ((value.iVal < INT_MIN || value.iVal > INT_MAX) || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << value.iVal << std::endl;

	std::cout << CYAN << "float: " << RESET;
	if ((value.fVal < FLOAT_MIN || value.fVal > FLOAT_MAX) || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << value.fVal << std::endl;

	std::cout << CYAN << "double: " << RESET;
	if ((value.dVal < DOUBLE_MIN || value.dVal > DOUBLE_MIN) || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << value.dVal << std::endl;
}

void	printPseudo(std::string const& input)
{
		if (input == "nan" || input == "nanf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (input == "+inf" || input == "+inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if (input == "-inf" || input == "-inff")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}
