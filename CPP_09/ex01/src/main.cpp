
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
		std::cerr << "usage:\nRPN [rpn expression]";
	}
	else
	{
		for (int i = 1;  i < ac; i++)
			expression.append(av[i]);
	}

	RPN rpn(expression);

	rpn.printSolution();
}
