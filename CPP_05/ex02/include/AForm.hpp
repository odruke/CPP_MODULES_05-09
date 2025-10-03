#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include "colors.hpp"

class Bureaucrat;

enum gradeType{
	SIGN,
	EXEC
};

class AForm
{
private:
	const std::string	_name;
	bool				_isSigned;
	const int			_minGradeToSign;
	const int			_minGradeToExec;
public:

//canonic form
	AForm(const std::string name, const int gradeToSign, const int gradeToExec);
	AForm(AForm const& copy);
	AForm& operator=(AForm const& other);

	virtual ~AForm();

//getters and setters
	int	getGradeToSign() const;
	int	getGradeToExec() const;
	bool		getIsSigned() const;
	const std::string&	getName() const;
	void	setSigned();

//member functions
	void	beSigned(Bureaucrat const& buro);
	virtual void	execute(Bureaucrat const& executor) const = 0;

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

	class FormNotSigned : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class AlreadySigned : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

std::ostream	&operator<<(std::ostream& o, AForm const& form);
#endif
