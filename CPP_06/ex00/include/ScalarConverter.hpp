#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#define ARRAY_SIZE(array)((int)(sizeof(array) / sizeof(array[0])))
#define INT_MIN std::numeric_limits<int>::min()
#define INT_MAX std::numeric_limits<int>::max()
#define FLOAT_MIN (-std::numeric_limits<float>::max())
#define FLOAT_MAX std::numeric_limits<float>::max()
#define DOUBLE_MIN (-std::numeric_limits<double>::max())
#define DOUBLE_MAX std::numeric_limits<double>::max()
#define INFF std::numeric_limits<float>::infinity()
#define NINFF (-std::numeric_limits<float>::infinity())
#define INF std::numeric_limits<double>::infinity()
#define NINF (-std::numeric_limits<double>::infinity())

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

struct ConvertedValue
{
	char		cValue;
	bool		cImpossible;
	bool		cNonDysp;
	int			iValue;
	bool		iImpossible;
	float		fValue;
	bool		fImpossible;
	double		dValue;
	bool		dImpossible;
	size_t		decim;
};


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
void	convertFromChar(std::string const& input);
void	convertFromInt(std::string const& input);
void	convertFromFloat(std::string const& input);
void	convertFromDouble(std::string const& input);
void	mainPrint(ConvertedValue value, e_type type);

#endif
