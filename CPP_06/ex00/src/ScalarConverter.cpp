#include "ScalarConverter.hpp"
#include "colors.hpp"
#include <string>
#include <cctype>

static bool	isPseudo(std::string const& input)
{
	std::string	specials[] = {"nan", "nanf", "+inf", "+inff", "-inf", "-inff"};
	if (input.length() == 1 || !isprint(input[0]) || isdigit(input[0]))
		return false;
	for (int i = 0; i < ARRAY_SIZE(specials); i++)
	{
		if (specials[i] == input)
			return true;
	}
	return false;
}

static bool	isChar(std::string const& input)
{
	if (input.length() > 1 || isdigit(input[0]))
		return false;
	return true;
}

static bool	isInt(std::string const& input)
{
	size_t i = 0;
	if (input[0] == '+' || input[0] == '-')
		i++;
	for (i = i; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}

static bool	isFloat(std::string const& input)
{
	std::string	validEnd = "fF";
	size_t i = 0;
	if ((input[0] == '+' || input[0] == '-'))
		i++;
	if (!isdigit(input[i]))
		return false;
	for (i = i; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
			break ;
	}
	if (input[i] != '.')
		return false;
	for (i = i + 1; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
			break ;
	}
	if (i != (input.length() - 1) || validEnd.find(input[i]) == std::string::npos)
		return false;
	return true;
}

static bool	isDouble(std::string const& input)
{
	size_t i = 0;
	if ((input[0] == '+' || input[0] == '-'))
		i++;
	if (!isdigit(input[i]))
		return false;
	for (i = i; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
			break ;
	}
	if (input[i] != '.')
		return false;
	for (i = i + 1; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
			break ;
	}
	if (i != input.length())
		return false;
	return true;
}

e_type wichType(std::string const& input)
{
	bool	(*allTypes[])(std::string const& input) = {&isPseudo, &isChar, &isInt, &isFloat, &isDouble};

	for (int i = PSEUDO; i < ARRAY_SIZE(allTypes); i++)
	{
		if (allTypes[i](input))
			return static_cast<e_type>(i);
	}
	return UNKNOWN;
}

void	ScalarConverter::convert(std::string const& input)
{
	std::string	typeName[] = {"Pseudo-literal", "char", "int", "float", "double", "unknown type"};
	e_type	thisType = wichType(input);
	if (thisType > ARRAY_SIZE(typeName))
	{
		std::cerr << RED << "typeName do not match enum e_type" << RESET << std::endl;
		return ;
	}
	std::cout <<  YELLOW << "The input is type: " << GREEN << typeName[thisType] << RESET << std::endl;

	switch (thisType)
	{
		case PSEUDO:
			printPseudo(input);
			break;
		case CHAR:
			convertFromChar(input);
			break;
		case INT:
			convertFromInt(input);
			break;
		case FLOAT:
			convertFromFloat(input);
			break;
		case DOUBLE:
			convertFromDouble(input);
			break;
		default:
			mainPrint((ConvertedValue){}, thisType);
			break;
	}
}
