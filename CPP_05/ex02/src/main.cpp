#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "colors.hpp"

int	main()
{
//declare bureaucrats and forms
	Bureaucrat	hermes("Hermes Conrad", 34);
	Bureaucrat	numberone("Number 1.0", 1);
	Bureaucrat	morgan("Morgan Proctor", 19);
	Bureaucrat	vogel("Warden Vogel", 135);

	ShrubberyCreationForm		plantSomeTree("acacia");
	RobotomyRequestForm			robotomy("Bender");
	PresidentialPardonForm		pardon("Philip J. fry");

//announce bureaucrats
	std::cout << "\nA bureaucrat named " << MAGENTA << hermes.getName().c_str() << RESET
			<< " with grade " << ORANGE << hermes.getGrade() << RESET<< " has been instantiated" << std::endl;
	std::cout << "A bureaucrat named " << MAGENTA << numberone.getName().c_str() << RESET
			<< " with grade " << ORANGE << numberone.getGrade() << RESET <<" has been instantiated" << std::endl;
	std::cout << "A bureaucrat named " << MAGENTA << vogel.getName().c_str() << RESET
			<< " with grade " << ORANGE << vogel.getGrade() << RESET <<" has been instantiated" << std::endl;
	std::cout << "A bureaucrat named " << MAGENTA << morgan.getName().c_str() << RESET
			<< " with grade " << ORANGE << morgan.getGrade() << RESET <<" has been instantiated" << std::endl;

	std::cout << std::endl;

//announce forms
	std::cout << "Form " << plantSomeTree << " needs a "
			<< GREEN << plantSomeTree.getGradeToSign() << RESET
			<<" level bureaucrat to sign it, and a "
			<< GREEN << plantSomeTree.getGradeToExec() << RESET
			<< " to execute it.\n";
	std::cout << "Form " << robotomy << " needs a "
			<< GREEN << robotomy.getGradeToSign() << RESET
			<< " level bureaucrat to sign it, and a "
			<< GREEN << robotomy.getGradeToExec() << RESET
			<< " to execute it.\n";
	std::cout << "Form " << pardon << " needs a "
			<< GREEN << pardon.getGradeToSign() << RESET
			<< " level bureaucrat to sign it, and a "
			<< GREEN << pardon.getGradeToExec() << RESET
			<< " to execute it.\n";

//degrade hermes because
	while (hermes.getGrade() < 150)
		hermes.decrementGrade();
	std::cout << "\n" << hermes << " has been degraded" << std::endl;

/* ============== test 1 ============= */
	std::cout << YELLOW << "\n============== test 1: try to execute non signed contracts ============= \n" << RESET << std::endl;

//checking that forms are in fact unsigned
	std::cout << "Form " << plantSomeTree << " is currently " << (plantSomeTree.getIsSigned()? "signed" : "unsigned") << std::endl;
	std::cout << "Form " << robotomy << " is currently " << (robotomy.getIsSigned()? "signed" : "unsigned") << std::endl;
	std::cout << "Form " << pardon << " is currently " << (pardon.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;


//trying to execute forms and checking they are still unsigned after
	hermes.executeForm(plantSomeTree);
	std::cout << "Form " << plantSomeTree << " is currently " << (plantSomeTree.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;

	numberone.executeForm(plantSomeTree);
	std::cout << "Form " << plantSomeTree << " is currently " << (plantSomeTree.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;

	morgan.executeForm(robotomy);
	std::cout << "Form " << robotomy << " is currently " << (robotomy.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;

	morgan.executeForm(pardon);
	std::cout << "Form " << pardon << " is currently " << (pardon.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;



/* ============== test 2 ============= */
	std::cout << YELLOW << "\n============== test 2: sign and execute ============= \n" << RESET << std::endl;

	std::cout << YELLOW << "Signing contracts" << RESET << std::endl;
	std::cout << "Form type: " << GREEN << "ShrubberyCreationForm" << RESET << std::endl;
	numberone.signForm(plantSomeTree);
	hermes.signForm(plantSomeTree);

	std::cout << "\nForm type: " << GREEN << "RobotomyRequestForm" << RESET << std::endl;
	vogel.signForm(robotomy);
	morgan.signForm(robotomy);

	std::cout << "\nForm type: " << GREEN << "PresidentialPardonForm" << RESET << std::endl;
	morgan.signForm(pardon);
	numberone.signForm(pardon);

	std::cout << YELLOW << "\nExecuting contracts" << RESET << std::endl;
	std::cout << "Form type: " << GREEN << "ShrubberyCreationForm" << RESET << std::endl;
	hermes.executeForm(plantSomeTree);
	numberone.executeForm(plantSomeTree);

	std::cout << "\nForm type: " << GREEN << "RobotomyRequestForm" << RESET << std::endl;
	morgan.executeForm(robotomy);
	vogel.executeForm(robotomy);

	std::cout << "\nForm type: " << GREEN << "PresidentialPardonForm" << RESET << std::endl;
	morgan.executeForm(pardon);
	numberone.executeForm(pardon);
}
