#include "Bureaucrat.hpp"
#include "form.hpp"
#include "colors.hpp"

int	main()
{
	Bureaucrat	hermes("Hermes Conrad", 34);
	Bureaucrat	numberone("Number 1.0", 1);
	Form		importantForm("super form", 1, 1);
	Form		regularForm("form", 100, 100);

	std::cout << "\nA bureaucrat named " << MAGENTA << hermes.getName().c_str() << RESET
			<< " with grade " << ORANGE << hermes.getGrade() << RESET<< " has been instantiated" << std::endl;
	std::cout << "\nA bureaucrat named " << MAGENTA << numberone.getName().c_str() << RESET
			<< " with grade " << ORANGE << numberone.getGrade() << RESET <<" has been instantiated\n" << std::endl;

	std::cout << importantForm << " needs a " << importantForm.getGradeToSign() << " level bureaucrat to sign it, and a "
			<< importantForm.getGradeToExec() << " to execute it.\n"
			<< regularForm << " needs a " << regularForm.getGradeToSign() << " level bureaucrat to sign it, and a "
			<< regularForm.getGradeToExec() << " to execute it.\n"<< std::endl;

/* ============== test 1 ============= */
	std::cout << YELLOW << "\n============== test 1: try to sign contracts ============= \n" << RESET << std::endl;

	std::cout << "Form " << importantForm << " is currently " << (importantForm.getIsSigned()? "signed\n" : "unsigned\n")
			<< "Form " << regularForm << " is currently " << (importantForm.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;

	std::cout << YELLOW << "\nsign attemtps" << RESET << std::endl;

	hermes.signForm(importantForm);
	hermes.signForm(regularForm);
	std::cout << "Form " << importantForm << " is currently " << (importantForm.getIsSigned()? "signed\n" : "unsigned\n")
			<< "Form " << regularForm << " is currently " << (regularForm.getIsSigned()? "signed\n" : " unsigned\n") << std::endl;

	numberone.signForm(importantForm);
std::cout << "Form " << importantForm << " is currently " << (importantForm.getIsSigned()? "signed\n" : "unsigned\n") << std::endl;
}
