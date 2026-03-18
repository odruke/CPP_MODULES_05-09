
#include "colors.hpp"
#include "RPN.hpp"

int	main(int ac, char **av)
{
	std::string expression;
	if (ac == 2 )
	{
		expression = av[1];
	}
	else if (ac < 2)
	{
		std::cerr << "usage:\nRPN [rpn expression]" << std::endl;
		return 1;
	}
	else
	{
		for (int i = 1;  i < ac; i++)
		{
			if (i > 1)
				expression += ' ';
			expression += av[i];
		}
	}

	try
	{
		RPN rpn(expression);
		rpn.printSolution();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
