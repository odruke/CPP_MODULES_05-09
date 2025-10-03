#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
private:
	std::string	_target;

public:
//canonic form
	ShrubberyCreationForm(std::string const& target);
	ShrubberyCreationForm(ShrubberyCreationForm const& copy);
	ShrubberyCreationForm&	operator=(ShrubberyCreationForm const& other);
	~ShrubberyCreationForm();

//member functions
	void	execute(Bureaucrat const& executor) const;
};

#endif
