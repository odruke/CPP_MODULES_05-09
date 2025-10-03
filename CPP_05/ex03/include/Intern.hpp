#ifndef INTERN_HPP
# define INTERN_HPP
#include "AForm.hpp"

class Intern
{
public:
//canonic form
	Intern();
	Intern(Intern const& copy);
	Intern&	operator=(Intern const& other);

	~Intern();
//member functions
	AForm*	makeForm(std::string const& form, std::string const& target);

//exceptions
	// class FormNotFound : public std::exception
	// {
	// public:
	// 	virtual const char*	what() const throw();
	// };

};


#endif
