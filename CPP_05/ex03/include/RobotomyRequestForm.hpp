#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP
#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
private:
	std::string	_target;
public:
//canonic form
	RobotomyRequestForm(std::string const& target);
	RobotomyRequestForm(RobotomyRequestForm const& copy);
	RobotomyRequestForm&	operator=(RobotomyRequestForm const& other);
	~RobotomyRequestForm();
//member functions
	void	execute(Bureaucrat const& executor) const;
};

#endif
