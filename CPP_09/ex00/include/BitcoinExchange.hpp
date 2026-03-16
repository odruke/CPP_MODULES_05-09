#pragma once

#include "colors.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <limits>

#ifndef DATABASE
# define DATABASE "./databases/data.csv"
#endif

#define DB_EXCEPTION(msg, fileLine) DBFormatUnknownExcp(__FILE__, __LINE__, msg, fileLine)


#define FLOAT_MAX std::numeric_limits<float>::max()
#define DOUBLE_MAX std::numeric_limits<double>::max()
#define MAX_BTC_INPUT 1000

struct MyFile
{
	std::ifstream	file;
	size_t			fileLine;
};

class BitcoinExchange {

	private:

		std::map<std::string, double>	_rates;

	//tools
		double		_toDouble(std::string const& num);
		std::string	_extractDateNumbers(std::string const& date, size_t pos, size_t len);
		bool		_validateMonth(int const& year, int const& month, int const& day);
		bool		_validateDate(std::string const& year, std::string const& month, std::string const& day);
		bool		_isLapYear(int const& year);
		bool		_isFinite(double n);

	//database functions
		void		_importDataBase(MyFile& database);
		double		_extractDbValue(std::string const& line, size_t fileLine);
		std::string	_extractDbDate(std::string const& line, size_t fileLine);

	//input functions
		double		_extractInputValue(std::string const& line);
		std::string	_extractInputDate(std::string const& line);
		double	_convertamount(std::string const& date, double const& ammout);

	public:
		//canonical form
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const& copy);
		BitcoinExchange&	operator=(BitcoinExchange const& other);
		~BitcoinExchange();

	//public methods
		void	processInput(std::string const& input);


		class FileNotFoundExcp : public std::exception
		{
			public:
				FileNotFoundExcp();
				virtual ~FileNotFoundExcp() throw();
				virtual const char *what() const throw();
		};

		class DBFormatUnknownExcp : public std::exception
		{
			private:
				std::string	_msg;
			public:
				DBFormatUnknownExcp(std::string const& file, int line, std::string msg, size_t dbLine);
				virtual ~DBFormatUnknownExcp() throw();
				virtual const char* what() const throw();
		};

		class InputBadFormat : public std::exception
		{
			private:
				std::string	_msg;
			public:
				InputBadFormat(std::string msg);
				virtual ~InputBadFormat() throw();
				virtual const char* what() const throw();
		};
};
