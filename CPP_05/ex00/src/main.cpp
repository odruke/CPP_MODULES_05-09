#include "Bureaucrat.hpp"
#include "colors.hpp"

int	main()
{
	Bureaucrat	*Manuel = new Bureaucrat("manuel", 150);

	std::cout << "a bureaucrat named " << Manuel->getName().c_str()
			<< " with grade " << Manuel->getGrade() << " has been instantiated" << std::endl;

/* ============== test 1 ============= */
	std::cout << YELLOW << "============== test 1============= " << RESET << std::endl;
	std::cout << "degrading " << BLUE << *Manuel << RESET << std::endl;
	try
	{
		Manuel->decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\ncurrent state of Bureaucrat: "
			<< BLUE << *Manuel << "\n" <<  RESET << std::endl;

/* ============== test 2 ============= */
	std::cout << YELLOW << "============== test 2 ============= " << RESET << std::endl;
	Manuel->setGrade(1);
	std::cout << "promoting " << BLUE << *Manuel << RESET << std::endl;
	try
	{
		Manuel->incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\ncurrent state of Bureaucrat: "
			<< BLUE << *Manuel << "\n" <<  RESET << std::endl;

/* ============== test 3 ============= */
	std::cout << YELLOW << "============== test 3 ============= " << RESET << std::endl;
	std::cout << "degrading " << BLUE << *Manuel << RESET << std::endl;
	try
	{
		Manuel->decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\ncurrent state of Bureaucrat: "
			<< BLUE << *Manuel << "\n" <<  RESET << std::endl;

/* ============== test 4 ============= */
	std::cout << YELLOW << "============== test 4 ============= " << RESET << std::endl;
	std::cout << "promoting " << BLUE << *Manuel << RESET << std::endl;
	try
	{
		Manuel->incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\ncurrent state of Bureaucrat: "
			<< BLUE << *Manuel << "\n" <<  RESET << std::endl;

/* ============== test 5 ============= */
	std::cout << YELLOW << "============== test 5 ============= " << RESET << std::endl;
	std::cout << "trying to manually set multiple incorrect values" << std::endl;
	try
	{
		Manuel->setGrade(-5);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
		std::cout << "\ncurrent state of Bureaucrat: "
			<< BLUE << *Manuel << "\n" <<  RESET << std::endl;
	try
	{
		Manuel->setGrade(2147483647);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "\ncurrent state of Bureaucrat: "
		<< BLUE << *Manuel << "\n" <<  RESET << std::endl;

	delete Manuel;
}
