#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

/* ========== Constructors and destructor ==============*/
PresidentialPardonForm::PresidentialPardonForm(std::string const& target)
: AForm("PresidentialPardonForm", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const& copy)
: AForm("PresidentialPardonForm", copy.getGradeToSign(), copy.getGradeToExec()), _target(copy._target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}


/* ========== member functions ==============*/
void	PresidentialPardonForm::execute(Bureaucrat const& executor) const
{
	if (executor.getGrade() > this->getGradeToExec())
		throw GradeTooLowException(executor.getGrade(), EXEC);
	else if (this->getIsSigned() == false)
		throw FormNotSigned();
	else
	{
		std::cout << GREEN << this->_target << RESET
				<< " has been pardoned by Zaphod Beeblebrox."
				<< std::endl;
	}
}


/* ========== overload operators ==============*/
PresidentialPardonForm&	PresidentialPardonForm::operator=(PresidentialPardonForm const& other)
{
	(void)other;
	return *this;
}

