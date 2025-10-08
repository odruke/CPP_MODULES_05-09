#include "ScalarConverter.hpp"
#include "colors.hpp"

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << ORANGE << "\nTEST 1: a" << RESET << std::endl;
		ScalarConverter::convert("a");

		std::cout << ORANGE << "\nTEST 2: 1" << RESET << std::endl;
		ScalarConverter::convert("1");

		std::cout << ORANGE << "\nTEST 3: 1.2f" << RESET << std::endl;
		ScalarConverter::convert("1.2f");

		std::cout << ORANGE << "\nTEST 4: 1.2" << RESET << std::endl;
		ScalarConverter::convert("1.2");

		std::cout << ORANGE << "\nTEST 5: should fail" << RESET << std::endl;
		ScalarConverter::convert("patata");

		std::cout << ORANGE << "\nTEST 6: should fail" << RESET << std::endl;
		ScalarConverter::convert(".2");

		std::cout << ORANGE << "\nTEST 7: should fail" << RESET << std::endl;
		ScalarConverter::convert("1..3");

		std::cout << ORANGE << "\nTEST 8: should fail" << RESET << std::endl;
		ScalarConverter::convert("1.2.3");

		std::cout << ORANGE << "\nTEST 9: should fail" << RESET << std::endl;
		ScalarConverter::convert("1.a");

		std::cout << ORANGE << "\nTEST 10: should fail" << RESET << std::endl;
		ScalarConverter::convert("1.f1");

		std::cout << ORANGE << "\nTEST 11: 98" << RESET << std::endl;
		ScalarConverter::convert("98");

		std::cout << ORANGE << "\nTEST 12: FLOAT_MAX" << RESET << std::endl;
		ScalarConverter::convert("340282346638528859811704183484516925440.0f");

		std::cout << ORANGE << "\nTEST 13: FLOAT_MIN" << RESET << std::endl;
		ScalarConverter::convert("-340282346638528859811704183484516925440.0f");

		std::cout << ORANGE << "\nTEST 14: DOUBLE_MAX" << RESET << std::endl;
		ScalarConverter::convert("179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0");

		std::cout << ORANGE << "\nTEST 15: DOUBLE_MIN" << RESET << std::endl;
		ScalarConverter::convert("-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.0");

		//PRINTING MAX TYPES FOR TESTING:
		// std::cout << "\n\n" << FLOAT_MAX << "\n" << FLOAT_MIN << "\n" << DOUBLE_MAX << "\n" << DOUBLE_MIN << std::endl;

	}
	else if (ac == 2)
		ScalarConverter::convert(av[1]);
	else
		std::cerr << "Too many arguments" << std::endl;
}
