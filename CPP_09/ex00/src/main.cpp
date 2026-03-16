
#include "BitcoinExchange.hpp"



int	main(int ac, char **av)
{
	if (ac > 2)
	{
		std::cerr << "Error: Too many arguments." << std::endl;
		return 1;
	}
	else if (ac < 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::string	inputFile = av[1];
	try
	{
		BitcoinExchange	exchange;
		exchange.processInput(inputFile);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	//1.- check for the database to exist, if not exit the program
	//2.- check for the database to be correct, if not exit the program.
	//3.- pass the input and convert
}
