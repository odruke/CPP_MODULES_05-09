#include "AForm.hpp"
#include "Bureaucrat.hpp"

/* ========== Constructors and destructor ==============*/

AForm::AForm(const std::string name, const int gradeToSign, const int gradeToExec)
: _name(name), _isSigned(false), _minGradeToSign(gradeToSign), _minGradeToExec(gradeToExec)
{
	const int	exec = this->_minGradeToExec;
	const int	sign = this->_minGradeToSign;
	if (exec < 1)
		throw GradeTooHighException(exec, EXEC);
	else if (sign < 1)
		throw GradeTooHighException(sign, SIGN);
	else if (exec > 150)
		throw GradeTooLowException(exec, EXEC);
	else if (sign > 150)
		throw GradeTooLowException(exec, SIGN);
}

AForm::AForm(AForm const& copy)
: _name(copy._name), _isSigned(false), _minGradeToSign(copy._minGradeToSign), _minGradeToExec(copy._minGradeToExec){}

AForm&	AForm::operator=(AForm const& other)
{
	if (this == &other)
		return *this;

	this->_isSigned = other._isSigned;

	//constant members can only be assigned at initialization
	//other than _isSigned will remain unchanged
	return *this;
}

AForm::~AForm(void) {}

/* ========== getters and setters ==============*/
int	AForm::getGradeToExec(void) const
{
	return this->_minGradeToExec;
}

int	AForm::getGradeToSign(void) const
{
	return this->_minGradeToSign;
}

const std::string&	AForm::getName(void) const
{
	return this->_name;
}

bool	AForm::getIsSigned(void) const
{
	return this->_isSigned;
}

void	AForm::setSigned(void)
{
	this->_isSigned = true;
}

/* ========== Member functions ==============*/
void	AForm::beSigned(Bureaucrat const& buro)//implement throw error for already signed
{

	if (this->_minGradeToSign < buro.getGrade())
		throw AForm::GradeTooLowException(buro.getGrade(), SIGN);
	else if (this->getIsSigned())
		throw AForm::AlreadySigned();
	else
		this->setSigned();
}


/* ========== Exceptions ==============*/

AForm::GradeTooHighException::GradeTooHighException(int grade, gradeType type)
{
	std::ostringstream oss;
	if (type == SIGN)
	{
		oss << RED << grade << RESET
			<< " is too high. Max grade to sign is "
			<< GREEN << "1" RESET;
	}
	else if (type == EXEC)
	{
		oss << RED << grade << RESET
			<< " is too high. Max grade to execute is "
			<< GREEN << "1" RESET;
	}
	this->_msg = oss.str();
}

AForm::GradeTooLowException::GradeTooLowException(int grade, gradeType type)
{
	std::ostringstream oss;
	if (type == SIGN)
	{
		oss << "Grade " << RED << grade << RESET
			<< " is too low to sign this form";
	}
	else if (type == EXEC)
	{
		oss << "Grade " << RED << grade << RESET
			<< " is too low to exec this form";
	}
	this->_msg = oss.str();
}

const char*	AForm::GradeTooHighException::what(void) const throw()
{
	return this->_msg.c_str();
}

const char* AForm::GradeTooLowException::what(void) const throw()
{
	return this->_msg.c_str();
}

AForm::GradeTooHighException::~GradeTooHighException() throw() {};
AForm::GradeTooLowException::~GradeTooLowException() throw() {};

const char*	AForm::FormNotSigned::what() const throw()
{
	return "Form is not signed";
}

const char* AForm::AlreadySigned::what() const throw()
{
	return "is already signed";
}

const char* AForm::InvalidForm::what() const throw()
{
	return "This is not a valid form";
}

/* ========== Overload operator ==============*/

std::ostream	&operator<<(std::ostream& o, AForm const& form)
{
	o << CYAN << form.getName().c_str() << RESET;
	return o;
}
