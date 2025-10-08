#include "ScalarConverter.hpp"
#include <cstdlib>
#include <cmath>
#include <cerrno>
#include <sstream>

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
	t_convertedValue converted = {};

	converted.cValue = input[0];
	converted.iValue = static_cast<int>(input[0]);
	converted.fValue = static_cast<float>(input[0]);
	converted.dValue = static_cast<double>(input[0]);
	converted.decim = 1;

	mainPrint(converted, CHAR);
}
/*strtoll and strtod, are more reiable functions than atol atof.. etc.
In case of overflow, they return a macro value (HUGE_VAL, LLONG_MAX) istead
of undefined behaviour. Due to precision probles with the decimals, all round to a TYPE_MAX
in case of a low overflow*/
void	convertFromInt(std::string const& input)
{
	t_convertedValue converted = {};
	long long int tmp = strtoll(input.c_str(), NULL, 10);

	if (tmp < INT_MIN || tmp > INT_MAX)
		converted.iImpossible = true;

	int i = static_cast<int>(tmp);

	if ((converted.cImpossible = (i < 0 || i > 127)) == false)
		converted.cNonDysp = (!isprint(i));
	converted.cValue = static_cast<char>(i);
	converted.iValue = i;
	converted.fValue = static_cast<float>(i);
	converted.dValue = static_cast<double>(i);
	converted.decim = 1;

	mainPrint(converted, INT);
}

static bool	OutOfBounds(double d, e_type type)
{
	switch (type)
	{
	case FLOAT:
		if (d != d) return true; //checks for nan (not a number) ||
		if (d == INFF || d == NINFF) return true; //checks for infinite
		// if (std::fabs(d) > std::pow(2, std::numeric_limits<float>::digits)) return true;//checks for bits absolute value. This check is for precision not overflow
		if (d < FLOAT_MIN || d > FLOAT_MAX) return true; //checks out of limits
		break;
	case DOUBLE:
		if (d != d) return true;
		if (d == INF || d == NINF) return true;
		// if (std::fabs(d) > std::pow(2, std::numeric_limits<double>::digits)) return true;
		if (d < DOUBLE_MIN || d > DOUBLE_MAX) return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

void	convertFromFloat(std::string const& input)
{
	t_convertedValue converted = {};

	errno = 0;
	float	f;
	double tmp = strtod(input.c_str(), NULL);
	if (errno == ERANGE || OutOfBounds(tmp, FLOAT))
		converted.fImpossible = true;

	if (!converted.fImpossible)
	{
		f = static_cast<float>(tmp);

		if ((converted.cImpossible = (f < 0 || f > 127)) == false)
			converted.cNonDysp = (!isprint(static_cast<int>(f)));
		converted.cValue = static_cast<char>(f);
		converted.iValue = static_cast<int>(f);
		converted.iImpossible = (f < INT_MIN || f > INT_MAX);
		converted.fValue = f;
		converted.dValue = static_cast<double>(f);
	}
	else
	{
		converted.cImpossible = true;
		converted.iImpossible = true;
		converted.dImpossible = true;
	}

	// converted.dImpossible = errno == ERANGE || OutOfBounds(f, DOUBLE);
	converted.decim = countDecimals(input, FLOAT);
	mainPrint(converted, FLOAT);
}

void	convertFromDouble(std::string const& input)
{
	t_convertedValue converted = {};

	errno = 0;
	double	d = strtod(input.c_str(), NULL);
	if (errno == ERANGE || OutOfBounds(d, DOUBLE))
		converted.dImpossible = true;

	if (!converted.dImpossible)
	{
		if ((converted.cImpossible = (d < 0 || d > 127)) == false)
			converted.cNonDysp = (!isprint(static_cast<int>(d)));
		converted.cValue = static_cast<char>(d);
		converted.iValue = static_cast<int>(d);
		converted.iImpossible = (d < INT_MIN || d > INT_MAX);
		converted.fValue = static_cast<float>(d);
		converted.fImpossible = (errno == ERANGE || OutOfBounds(d, FLOAT));
		converted.dValue = d;
	}
	else
	{
		converted.cImpossible = true;
		converted.iImpossible = true;
		converted.fImpossible = true;
	}

	converted.decim = countDecimals(input, DOUBLE);
	mainPrint(converted, DOUBLE);
}

