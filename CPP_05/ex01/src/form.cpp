#include "form.hpp"
#include "Bureaucrat.hpp"

/* ========== Constructors and destructor ==============*/

Form::Form(const std::string name, const int gradeToSign, const int gradeToExec)
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

Form::Form(Form const& copy)
: _name(copy._name), _isSigned(false), _minGradeToSign(copy._minGradeToSign), _minGradeToExec(copy._minGradeToExec){}

Form&	Form::operator=(Form const& other)
{
	if (this == &other)
		return *this;

	this->_isSigned = other._isSigned;

	//constant members can only be assigned at initialization
	//other than _isSigned will remain unchanged
	return *this;
}

Form::~Form(void) {}

/* ========== getters and setters ==============*/
int	Form::getGradeToExec(void) const
{
	return this->_minGradeToExec;
}

int	Form::getGradeToSign(void) const
{
	return this->_minGradeToSign;
}

const std::string&	Form::getName(void) const
{
	return this->_name;
}

bool	Form::getIsSigned(void) const
{
	return this->_isSigned;
}

void	Form::setSigned(void)
{
	this->_isSigned = true;
}

/* ========== Member functions ==============*/
void	Form::beSigned(Bureaucrat const& buro)
{
	if (this->_minGradeToSign < buro.getGrade())
		throw Form::GradeTooLowException(buro.getGrade(), SIGN);
	else
		this->setSigned();
}


/* ========== Exceptions ==============*/

Form::GradeTooHighException::GradeTooHighException(int grade, gradeType type)
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

Form::GradeTooLowException::GradeTooLowException(int grade, gradeType type)
{
	std::ostringstream oss;
	if (type == SIGN)
	{
		oss << "Grade " << RED << grade << RESET
			<< " is too low to sign";
	}
	else if (type == EXEC)
	{
		oss << "Grade " << RED << grade << RESET
			<< " is too low to exec";
	}
	this->_msg = oss.str();
}

const char*	Form::GradeTooHighException::what(void) const throw()
{
	return this->_msg.c_str();
}

const char* Form::GradeTooLowException::what(void) const throw()
{
	return this->_msg.c_str();
}

Form::GradeTooHighException::~GradeTooHighException() throw() {};
Form::GradeTooLowException::~GradeTooLowException() throw() {};

/* ========== Overload operator ==============*/

std::ostream	&operator<<(std::ostream& o, Form const& form)
{
	o << CYAN << form.getName().c_str() << RESET;
	return o;
}
