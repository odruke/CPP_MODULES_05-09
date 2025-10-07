#include "ScalarConverter.hpp"
#include "colors.hpp"
#include <string>
#include <cctype>

static bool	isPseudo(std::string const& input)
{
	std::string	specials[] = {"nan", "nanf", "+inf", "+inff", "-inf", "-inff"};
	if (input.length() > 1 || !isprint(input[0]) || isdigit(input[0]))
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
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[0] == '+' || input[0] == '-')
			i++;
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}

static bool	isFloat(std::string const& input)
{
	std::string	validEnd = "fF";
	size_t i;
	for (i = 0; i < input.length(); i++)
	{
		if (input[0] == '+' || input[0] == '-')
		{
			i++;
			if (!isdigit(input[i]))
				return false;
		}
		if (!isdigit(input[i]))
			break ;
	}
	if (input[i] != '.' && (input[i] == '.' && i == 0))
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
	size_t i;
	for (i = 0; i < input.length(); i++)
	{
		if (input[0] == '+' || input[0] == '-')
		{
			i++;
			if (!isdigit(input[i]))
				return false;
		}
		if (!isdigit(input[i]))
			break ;
	}
	if (input[i] != '.' || (input[i] == '.' && i == 0))
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
	char	c = static_cast<char>(input[0]);
	int		i = static_cast<int>(input[0]);
	float	f = static_cast<float>(input[0]);
	double	d = static_cast<double>(input[0]);

	mainPrint((t_convertedValue){.cVal = c, .iVal = i, .fVal = f, .dVal = d}, thisType);
	// switch (thisType)
	// {
	// case PSEUDO:
	// 	printPseudo(input);
	// 	break;
	// case CHAR:
	// 	printChar(input);
	// 	break;
	// case INT:
	// 	printInt(input);
	// 	break;
	// case FLOAT:
	// 	printFloat(input);
	// 	break;
	// case DOUBLE:
	// 	printDouble(input);
	// default:
	// 	printUnknown(input);
	// 	break;
	// }
}
