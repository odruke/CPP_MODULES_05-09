#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP
#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
	std::string	_target;
public:
//canonic form
	PresidentialPardonForm(std::string const& target);
	PresidentialPardonForm(PresidentialPardonForm const& copy);
	PresidentialPardonForm&	operator=(PresidentialPardonForm const& other);
	~PresidentialPardonForm();

//member functions
	void	execute(Bureaucrat const& executor) const;
};

#endif
