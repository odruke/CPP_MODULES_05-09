#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#define ARRAY_SIZE(array)((int)(sizeof(array) / sizeof(array[0])))
#define INT_MIN std::numeric_limits<int>::min()
#define INT_MAX std::numeric_limits<int>::max()
#define FLOAT_MIN std::numeric_limits<float>::min()
#define FLOAT_MAX std::numeric_limits<float>::max()
#define DOUBLE_MIN std::numeric_limits<double>::min()
#define DOUBLE_MAX std::numeric_limits<double>::max()

#include <limits>
#include <iostream>

enum e_type{
	PSEUDO,
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	UNKNOWN
};

enum e_options{
	OK,
	IMPOSSIBLE,
	NONDISPLAY
};

typedef struct e_convertedValue
{
	char		cVal;
	int			iVal;
	float		fVal;
	double		dVal;
}	t_convertedValue;


class ScalarConverter
{
private:
//canonic form
	ScalarConverter();//no instantiable
	ScalarConverter(ScalarConverter const& copy);
	ScalarConverter&	operator=(ScalarConverter const& other);
	~ScalarConverter();
public:
//member functions
	static void	convert(std::string const& input);
};


//printing functions
void	printPseudo(std::string const& input);
void	printChar(std::string const& input);
void	printInt(std::string const& input);
void	printFloat(std::string const& input);
void	printDouble(std::string const& input);
void	printUnknown(std::string const& input);
void	mainPrint(t_convertedValue value, e_type type);

#endif
