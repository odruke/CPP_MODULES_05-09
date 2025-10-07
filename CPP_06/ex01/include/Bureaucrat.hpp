#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "colors.hpp"

class Form;

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;
public:
//constructora and destructor
	Bureaucrat();
	Bureaucrat(std::string const& name, int grade);
	Bureaucrat(std::string const& name);
	~Bureaucrat();
	Bureaucrat(Bureaucrat const& copy);

	Bureaucrat	&operator=(Bureaucrat const& other);

//getters & setters
	std::string	getName() const;
	int			getGrade() const;
	void		setGrade(int grade);

//Member functions
	void	incrementGrade();
	void	decrementGrade();
	void	signForm(Form& form);

//exceptions

	class GradeTooHighException : public std::exception
	{
	private:
		std::string _msg;
	public:
		GradeTooHighException(int grade);
		virtual ~GradeTooHighException() throw();
		virtual const char *what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	private:
		std::string _msg;
	public:
		GradeTooLowException(int grade);
		virtual ~GradeTooLowException() throw();
		virtual const char *what() const throw();
	};
};

//insertion overload
std::ostream	&operator<<(std::ostream & o, Bureaucrat const& buro);

#endif
