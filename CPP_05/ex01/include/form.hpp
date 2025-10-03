#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include "colors.hpp"

class Bureaucrat;

enum gradeType{
	SIGN,
	EXEC
};

class Form
{
private:
	const std::string	_name;
	bool				_isSigned;
	const int			_minGradeToSign;
	const int			_minGradeToExec;
public:

//canonic form
	Form(const std::string name, const int gradeToSign, const int gradeToExec);
	Form(Form const& copy);
	Form& operator=(Form const& other);

	~Form();

//getters and setters
	int	getGradeToSign() const;
	int	getGradeToExec() const;
	bool		getIsSigned() const;
	const std::string&	getName() const;
	void	setSigned();

//member functions
	void	beSigned(Bureaucrat const& buro);

//exceptions
	class GradeTooHighException : public std::exception
	{
	private:
		std::string _msg;

	public:
		GradeTooHighException(int grade, gradeType type);
		virtual ~GradeTooHighException() throw();
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	private:
		std::string _msg;

	public:
		GradeTooLowException(int grade, gradeType type);
		virtual ~GradeTooLowException() throw();
		virtual const char* what() const throw();
	};

};

std::ostream	&operator<<(std::ostream& o, Form const& form);
#endif
