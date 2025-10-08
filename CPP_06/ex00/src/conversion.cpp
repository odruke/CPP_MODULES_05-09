#include "ScalarConverter.hpp"
#include <cstdlib>

static size_t	countDecimals(std::string const& input, e_type type)
{
	size_t deci = input.length() - input.find('.') - 1;
	if (type == FLOAT && deci > 0)
		deci -= 1;
	if (type == FLOAT && deci > 6)
		deci = 6;
	if (type == DOUBLE && deci > 14)
		deci = 14;
	if (deci == 0)
		deci = 1;
	return deci;
}

void	convertFromChar(std::string const& input)
{
	t_convertedValue converted = {};

	converted.cValue = input[0];
	converted.iValue = static_cast<int>(input[0]);
	converted.fValue = static_cast<float>(input[0]);
	converted.dValue = static_cast<double>(input[0]);
	converted.decim = 1;

	mainPrint(converted, CHAR);
}

void	convertFromInt(std::string const& input)
{
	t_convertedValue converted = {};
	long long int tmp = atoll(input.c_str());
	int	i;
	if (tmp < INT_MIN || tmp > INT_MAX)
		converted.iImpossible = true;

	i = static_cast<int>(tmp);

	if ((converted.cImpossible = (i < 0 || i > 127)) == false)
		converted.cNonDysp = (!isprint(i));
	converted.cValue = static_cast<char>(i);
	converted.iValue = i;
	converted.fValue = static_cast<float>(i);
	converted.dValue = static_cast<double>(i);
	converted.decim = 1;

	mainPrint(converted, INT);
}

void	convertFromFloat(std::string const& input)
{
	t_convertedValue converted = {};
	double tmp = atof(input.c_str());
	float	f;
	if (tmp < FLOAT_MIN || tmp > FLOAT_MAX)
		converted.fImpossible = true;

	f = static_cast<float>(tmp);

	if ((converted.cImpossible = (f < 0 || f > 127)) == false)
		converted.cNonDysp = (!isprint(f));
	converted.cValue = static_cast<char>(f);
	converted.iValue = static_cast<int>(f);
	converted.iImpossible = (tmp < INT_MIN || tmp > INT_MAX);
	converted.fValue = f;
	converted.dValue = static_cast<double>(f);
	converted.decim = countDecimals(input, FLOAT);

	mainPrint(converted, FLOAT);
}

void	convertFromDouble(std::string const& input)
{
	t_convertedValue converted = {};
	double tmp = atof(input.c_str());
	double	d;
	if (tmp < DOUBLE_MIN || tmp > DOUBLE_MAX)
		converted.dImpossible = true;

	d = static_cast<double>(tmp);

	if ((converted.cImpossible = (d < 0 || d > 127)) == false)
		converted.cNonDysp = (!isprint(d));
	converted.cValue = static_cast<char>(d);
	converted.iValue = static_cast<int>(d);
	converted.iImpossible = (tmp < INT_MIN || tmp > INT_MAX);
	converted.fValue = static_cast<float>(d);
	converted.fImpossible = (tmp < FLOAT_MIN || tmp > FLOAT_MAX);
	converted.dValue = d;
	converted.decim = countDecimals(input, DOUBLE);

	mainPrint(converted, DOUBLE);
}

