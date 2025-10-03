#include "Bureaucrat.hpp"

/* ========== Constructors and destructor ==============*/
Bureaucrat::Bureaucrat(void) : _name("Someone"), _grade(150) {}

Bureaucrat::Bureaucrat(std::string const& name) : _name(name), _grade(150) {}

Bureaucrat::Bureaucrat(std::string const& name, int grade) : _name(name){
	this->setGrade(grade);
}

Bureaucrat::Bureaucrat(Bureaucrat const& copy) : _name(copy._name)
{
	if (this != &copy){
		this->_grade = copy._grade;
	}
}

Bureaucrat::~Bureaucrat(void){}

/* ============== getters and setters ============= */

void	Bureaucrat::setGrade(int grade){
	if (grade < 1)
		throw GradeTooHighException(grade);
	else if (grade > 150)
		throw GradeTooLowException(grade);
	this->_grade = grade;
}

std::string	Bureaucrat::getName(void) const {return this->_name;}

int	Bureaucrat::getGrade(void) const {return this->_grade;}


/* ============== Member functions ============= */
void	Bureaucrat::decrementGrade(void)
{
	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException(this->_grade + 1);
	else
		this->_grade += 1;
}

void	Bureaucrat::incrementGrade(void)
{
	if (this->_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException(this->_grade - 1);
	else
		this->_grade -= 1;
}



/* ============== exceptions ============= */

Bureaucrat::GradeTooHighException::GradeTooHighException(int grade){
	std::ostringstream oss;
	oss << RED << grade << RESET
		<< " is too high. Max grade is "
		<< GREEN << "1" RESET;
	this->_msg = oss.str();
}

Bureaucrat::GradeTooLowException::GradeTooLowException(int grade){
	std::ostringstream oss;
	oss << RED << grade << RESET
		<< " is too low. Lower grade possible is "
		<< GREEN << "150" RESET;
	this->_msg = oss.str();
}

const char	*Bureaucrat::GradeTooHighException::what(void) const throw(){
	return this->_msg.c_str();
}

const char	*Bureaucrat::GradeTooLowException::what(void) const throw(){
	return this->_msg.c_str();
}

Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}

/* ============== insertion overaload ============= */
std::ostream	&operator<<(std::ostream& o, Bureaucrat const& buro){
	o << buro.getName().c_str() << ", bureaucrat grade " << buro.getGrade();
	return o;
}
