#include "ScalarConverter.hpp"
#include "colors.hpp"
#include <limits>
#include <cctype>
#include <cstdlib>
#include <iomanip>

void	mainPrint(t_convertedValue value, e_type type)
{
//PRINT CHAR
	std::cout << CYAN << "char: " << RESET;
	if (!isprint(value.cVal) || type == UNKNOWN)
		std::cout << RED << "Non displayable" << RESET << std::endl;
	else
		std::cout << "'" << value.cVal << "'" << std::endl;

//PRINT INT
	std::cout << CYAN << "int: " << RESET;
	if ((value.iVal < INT_MIN || value.iVal > INT_MAX) || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << value.iVal << std::endl;

//PRINT FLOAT
	std::cout << CYAN << "float: " << RESET;
	if ((value.fVal < FLOAT_MIN || value.fVal > FLOAT_MAX) || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << std::fixed << std::setprecision(value.decim) << value.fVal << "f" << std::endl;

//PRINT DOUBLE
	std::cout << CYAN << "double: " << RESET;
	if ((value.dVal < DOUBLE_MIN || value.dVal > DOUBLE_MAX) || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << std::fixed << std::setprecision(value.decim) << value.dVal << std::endl;
}

void	printPseudo(std::string const& input)
{
	if (input == "nan" || input == "nanf")
	{
		std::cout << CYAN << "char: " << RED << "impossible" << RESET << std::endl;
		std::cout << CYAN << "int: " << RED << "impossible" << RESET << std::endl;
		std::cout << CYAN << "float: " << RESET << "nanf" << std::endl;
		std::cout << CYAN << "double: " << RESET << "nan" << std::endl;
	}
	else if (input == "+inf" || input == "+inff")
	{
		std::cout << CYAN << "char: " << RED << "impossible" << RESET << std::endl;
		std::cout << CYAN << "int: " << RED << "impossible" << RESET << std::endl;
		std::cout << CYAN << "float: " << RESET << "+inff" << std::endl;
		std::cout << CYAN << "double: " << RESET << "+inf" << std::endl;
	}
	else if (input == "-inf" || input == "-inff")
	{
		std::cout << CYAN << "char: " << RED << "impossible" << RESET << std::endl;
		std::cout << CYAN << "int: " << RED << "impossible" << RESET << std::endl;
		std::cout << CYAN << "float: " << RESET << "-inff" << std::endl;
		std::cout << CYAN << "double: " << RESET << "-inf" << std::endl;
	}
}

