#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cctype>

/* ========== Constructors and destructor ==============*/
Intern::Intern(void) {}
Intern::Intern(Intern const& copy) {(void)copy;}
Intern::~Intern() {}

/* ========== makeform functions ==============*/

AForm*	makeShrubbery(std::string const& target)
{
	return new ShrubberyCreationForm(target);
}

AForm*	makeRobotomy(std::string const& target)
{
	return new RobotomyRequestForm(target);
}

AForm* makePardon(std::string const& target)
{
	return new PresidentialPardonForm(target);
}
/* ========== member functions ==============*/
AForm*	Intern::makeForm(std::string const& form, std::string const& target)
{
	AForm*	(*newForm[])(std::string const&) = {&makeShrubbery, &makeRobotomy, &makePardon};
	std::string	forms[] = {"shrubbery", "robotomy", "pardon"};
	std::string	formsNames[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};

	std::string normalizedForm;
	for (size_t i = 0; i < form.length(); i++)
		normalizedForm += std::tolower(static_cast<unsigned char>(form[i]));

	for (int i = 0; i < 3; i++)
	{
		if (normalizedForm.find(forms[i]) != std::string::npos)
		{
			std::cout << "Intern creates " << CYAN << formsNames[i] << RESET << std::endl;
			return newForm[i](target);
		}
	}
	std::cerr << "Form not found" << std::endl;
	return NULL;
}

/* ========== overload operator ==============*/
Intern&	Intern::operator=(Intern const& other)
{
	(void)other;
	return *this;
}

/* ========== exceptions ==============*/
// const char	*Intern::FormNotFound::what(void) const throw()
// {
// 	return "Form not found";
// }
