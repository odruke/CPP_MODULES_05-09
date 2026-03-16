#include "BitcoinExchange.hpp"

/*=================== CONSTRUCTORS AND DESTRUCTOR======================*/

BitcoinExchange::BitcoinExchange(void)
{
	MyFile	database;
	database.file.open(DATABASE);
	database.fileLine = 0;
	if (!database.file.is_open())
		throw DB_EXCEPTION("Could not open DataBase file", 0);
	this->_importDataBase(database);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& copy) : _rates(copy._rates) {}

BitcoinExchange::~BitcoinExchange(void) {}


/*==================== ASSIGN OPERATOR =================================================*/
BitcoinExchange&	BitcoinExchange::operator=(BitcoinExchange const& other)
{
	if (this != &other)
		this->_rates = other._rates;
	return *this;
}



/*===================== private functions ========================================*/

//TOOLS

bool BitcoinExchange::_isFinite(double n)
{
	if (n != n)
		return false;
	if (n > DOUBLE_MAX || n < -DOUBLE_MAX)
		return false;
	return true;
}

bool	BitcoinExchange::_isLapYear(int const& year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	return false;
}

double	BitcoinExchange::_toDouble(std::string const& num)//TODO check security
{
	std::istringstream streamNum(num);
	double	value;
	streamNum >> value;

	return value;
	// std::istringstream iss(num);
	// double value = 0.0;
	// char extra = '\0';

	// if (!(iss >> value) || (iss >> extra))
	// 	throw InputBadFormat("bad input => " + num);

	// if (this->_isFinite(value))
	// 	throw InputBadFormat("bad input => " + num);

	// return value;
}



std::string	BitcoinExchange::_extractDateNumbers(std::string const& date, size_t pos, size_t len)
{

	if (date.empty() || date.find_first_not_of("-0123456789") != std::string::npos)
		return "";

	std::string numbers = date.substr(pos, len);

	return numbers;
}

bool	BitcoinExchange::_validateMonth(int const& year, int const& month, int const& day)
{
	if (month < 1 || month > 12)
		return false;

	/* we rule out the lap year exception,
	so we can work with a consistent rule for february */
	if (month == 2 && day == 29)
	{
		if (this->_isLapYear(year))
			return true;
		else
			return false;
	}

	/* from january to july, odd numbers have 31 days,
	from august to december, its reversed. february will allways be max 28 */
	if (month < 8)
	{
		if ((month % 2 == 0 && day > 30) || (month == 2 && day > 28))
			return false;
	}
	else
	{
		if (month % 2 != 0 && day > 30)
			return false;
	}

	return true;
}

bool	BitcoinExchange::_validateDate(std::string const& year, std::string const& month, std::string const& day)
{
	int yearNb = static_cast<int>(this->_toDouble(year));
	int monthNb = static_cast<int>(this->_toDouble(month));
	int dayNb = static_cast<int>(this->_toDouble(day));

	if (yearNb < 2009 || yearNb > 2022)
		return false;
	if (dayNb < 1 || dayNb > 31)
		return false;
	if (!this->_validateMonth(yearNb, monthNb, dayNb))
		return false;

	return true;
}
// DATABASE FUNCTIONS
double	BitcoinExchange::_extractDbValue(std::string const& line, size_t fileLine)
{
	size_t pos = line.find(',');
	if (pos == std::string::npos || pos != 10)
		throw DB_EXCEPTION("Wrong date size or database separator format", fileLine);

	std::string strValue = line.substr(pos + 1);
	if (strValue.find_first_not_of("0123456789.") != std::string::npos)
		throw DB_EXCEPTION("Wrong database value format", fileLine);

	size_t frontDot = strValue.find_first_of(".");
	size_t backDot = strValue.find_last_of(".");

	if (frontDot != std::string::npos)
	{
		if (frontDot != backDot || frontDot == 0 || backDot == strValue.size() - 1)
			throw DB_EXCEPTION("Wrong database value format", fileLine);
	}

	double value = this->_toDouble(strValue);
	if (value > FLOAT_MAX)
		throw DB_EXCEPTION("Database value is too large", fileLine);
	if (value < 0)
		throw DB_EXCEPTION("Database value must be a positive number", fileLine);

	return value;
}

std::string	BitcoinExchange::_extractDbDate(std::string const& line, size_t fileLine)
{
	if (line.empty() || line.size() < 10)
		throw DB_EXCEPTION("wrong date format", fileLine);
	if (line.at(4) != '-' || line.at(7) != '-')
		throw DB_EXCEPTION("Wrong date format", fileLine);

	std::string date = line.substr(0, 10);
	std::string year = this->_extractDateNumbers(date, 0, 4);
	std::string month = this->_extractDateNumbers(date, 5, 2);
	std::string day = this->_extractDateNumbers(date, 8, 2);

	if (year.empty() || month.empty() || day.empty())
		throw DB_EXCEPTION("Wrong date format", fileLine);

	if (!this->_validateDate(year, month, day))
		throw DB_EXCEPTION("Wrong date format", fileLine);

	return date;
}

void	BitcoinExchange::_importDataBase(MyFile& database)
{
	//1 read line
	//1.5 skip first line
	//2 tokenize line
	//3 add to map key = date, value = exchange rate;

	std::string	line;

	while(std::getline(database.file, line))
	{
		database.fileLine++;
		if (database.fileLine == 1)
		{
			if (line != "date,exchange_rate")
				throw DB_EXCEPTION("Unkown DataBase header line", database.fileLine);
			continue;
		}

		std::string	date = this->_extractDbDate(line, database.fileLine);
		double		value = this->_extractDbValue(line, database.fileLine);

		this->_rates.insert(std::pair<std::string, double>(date, value));
	}

}
//INPUT FUNCTIONS
double	BitcoinExchange::_extractInputValue(std::string const& line)
{
	size_t pos = line.find(" | ");
	if (pos == std::string::npos)
		throw InputBadFormat("bad input => ");
	if (pos == std::string::npos || pos != 10)
		throw InputBadFormat("bad input => " + line);

	std::string strValue = line.substr(pos + 3);
	if (strValue.find_first_not_of("-0123456789.") != std::string::npos)
		throw InputBadFormat("bad input => " + strValue);

	size_t frontDot = strValue.find_first_of(".");
	size_t backDot = strValue.find_last_of(".");

	if (frontDot != std::string::npos)
	{
		if (frontDot != backDot || frontDot == 0 || backDot == strValue.size() - 1)
			throw InputBadFormat("bad input => " + strValue);
	}

	size_t frontMinus = strValue.find_first_of("-");
	size_t backMinus = strValue.find_last_of("-");

	if (frontMinus != std::string::npos)
	{
		if (frontMinus != backMinus || frontMinus != 0)
			throw InputBadFormat("bad input => " + strValue);
	}

	double value = this->_toDouble(strValue);
	if (value > FLOAT_MAX || value > MAX_BTC_INPUT)
			throw InputBadFormat("too large a number.");
	if (value < 0)
			throw InputBadFormat("not a positive number.");

	return value;
}

std::string	BitcoinExchange::_extractInputDate(std::string const& line)
{
	if (line.empty())
		throw InputBadFormat("bad input => ");
	if (line.size() < 10)
		throw InputBadFormat("bad input => " + line);

	std::string date = line.substr(0, 10);

	if (date.at(4) != '-' || date.at(7) != '-')
		throw InputBadFormat("bad input => " + date);

	std::string year = this->_extractDateNumbers(date, 0, 4);
	std::string month = this->_extractDateNumbers(date, 5, 2);
	std::string day = this->_extractDateNumbers(date, 8, 2);

	if (year.empty() || month.empty() || day.empty())
		throw InputBadFormat("bad input => " + date);

	if (!this->_validateDate(year, month, day))
		throw InputBadFormat("bad input => " + date);

	return date;
}

double	BitcoinExchange::_convertamount(std::string const& date, double const& amount)
{
	std::map<std::string, double>::iterator it = this->_rates.lower_bound(date);
	if ((it != _rates.end() && it->first == date) || it == _rates.begin())
		return it->second * amount;

	--it;
	return it->second * amount;
}
/*==================== Public functions ===============================================*/

void	BitcoinExchange::processInput(std::string const& input)
{
	MyFile	inputFile;
	inputFile.file.open(input.c_str());
	inputFile.fileLine = 0;
	if (!inputFile.file.is_open())
		throw FileNotFoundExcp();

	std::string	line;

	while(std::getline(inputFile.file, line))
	{
		inputFile.fileLine++;
		if (inputFile.fileLine == 1)
		{
			if (line != "date | value")
				throw InputBadFormat("Unkown input header line");
			continue;
		}
		try
		{
			std::string date = this->_extractInputDate(line);
			double amount = this->_extractInputValue(line);
			double value = this->_convertamount(date, amount);
			std::cout << date << " => " << amount << " = " << value << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

}

/*=================== Exceptions ===================================================*/

//constructors
BitcoinExchange::FileNotFoundExcp::FileNotFoundExcp(void) {}

BitcoinExchange::DBFormatUnknownExcp::DBFormatUnknownExcp(std::string const& file, int line, std::string msg, size_t dbLine)
{
	std::ostringstream oss;
	oss << RED << "Error at: " << RESET
		<< file  << ":" << line << "\n"
		<< RED << msg << ", around DataBase line " RESET
		<< "[" << dbLine << "]";
	this->_msg = oss.str();
}

BitcoinExchange::InputBadFormat::InputBadFormat(std::string msg)
{
	std::ostringstream oss;
	oss << "Error: " << msg;
	this->_msg = oss.str();
}
//what
const char*	BitcoinExchange::FileNotFoundExcp::what(void) const throw()
{
	return "Error: could not open file";
}

const char*	BitcoinExchange::DBFormatUnknownExcp::what(void) const throw()
{
	return this->_msg.c_str();
}

const char*	BitcoinExchange::InputBadFormat::what(void) const throw()
{
	return this->_msg.c_str();
}

//destructors
BitcoinExchange::FileNotFoundExcp::~FileNotFoundExcp(void) throw() {}

BitcoinExchange::DBFormatUnknownExcp::~DBFormatUnknownExcp(void) throw() {}

BitcoinExchange::InputBadFormat::~InputBadFormat(void) throw() {}




