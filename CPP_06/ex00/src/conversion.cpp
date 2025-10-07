#include "ScalarConverter.hpp"
#include <cstdlib>

static size_t	countDecimals(std::string const& input, e_type type)
{
	size_t deci = input.length() - input.find('.') - 1;
	if (type == FLOAT && deci > 0)
		deci -= 1;
	if (deci == 0)
		deci = 1;
	return deci;
}

void	convertFromChar(std::string const& input)
{
	char	c = static_cast<char>(input[0]);
	int		i = static_cast<int>(input[0]);
	float	f = static_cast<float>(input[0]);
	double	d = static_cast<double>(input[0]);

	mainPrint((t_convertedValue){.cVal = c, .iVal = i, .fVal = f, .dVal = d, .decim = 1}, CHAR);
}

void	convertFromInt(std::string const& input)
{
	int		i = atoi(input.c_str());

	char	c = static_cast<char>(i);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(i);

	mainPrint((t_convertedValue){.cVal = c, .iVal = i, .fVal = f, .dVal = d, .decim = 1}, INT);
}

void	convertFromFloat(std::string const& input)
{
	float	f = static_cast<float>(atof(input.c_str()));

	char	c = static_cast<char>(f);
	int		i = static_cast<int>(f);
	double	d = static_cast<double>(f);
	size_t	decim = countDecimals(input, FLOAT);

	mainPrint((t_convertedValue){.cVal = c, .iVal = i, .fVal = f, .dVal = d, .decim = decim}, FLOAT);
}

void	convertFromDouble(std::string const& input)
{
	double	d = atof(input.c_str());

	char	c = static_cast<char>(d);
	int		i = static_cast<int>(d);
	float	f = static_cast<float>(d);
	size_t	decim = countDecimals(input, DOUBLE);

	mainPrint((t_convertedValue){.cVal = c, .iVal = i, .fVal = f, .dVal = d, .decim = decim}, CHAR);
}

