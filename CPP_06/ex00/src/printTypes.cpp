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
	if (value.cImpossible)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
	{
		if (value.cNonDysp || type == UNKNOWN)
			std::cout << RED << "Non displayable" << RESET << std::endl;
		else
			std::cout << "'" << value.cValue << "'" << std::endl;
	}

//PRINT INT
	std::cout << CYAN << "int: " << RESET;
	if (value.iImpossible || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << value.iValue << std::endl;

//PRINT FLOAT
	std::cout << CYAN << "float: " << RESET;
	if (value.fImpossible || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << std::fixed << std::setprecision(value.decim > 6? 6 : value.decim)
				<< value.fValue << "f" << std::endl;

//PRINT DOUBLE
	std::cout << CYAN << "double: " << RESET;
	if (value.dImpossible || type == UNKNOWN)
		std::cout << RED << "impossible" << RESET << std::endl;
	else
		std::cout << std::fixed << std::setprecision(value.decim > 13? 13 : value.decim)
				<< value.dValue << std::endl;
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

