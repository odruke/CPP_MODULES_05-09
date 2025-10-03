#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <ctime>
#include <cstdlib>
#include <unistd.h>

int randomNumber(int max)
{
	static bool seeded = false;

	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	return rand() % (max + 1);
}

bool randomChance(void)
{
	return rand() % 2;
}

/* ========== Constructors and destructor ==============*/

RobotomyRequestForm::RobotomyRequestForm(std::string const& target)
: AForm("RobotomyRequestForm", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const& copy)
: AForm("RobotomyRequestForm", copy.getGradeToSign(), copy.getGradeToExec()), _target(copy._target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

/* ========== member functions ==============*/
void	RobotomyRequestForm::execute(Bureaucrat const& executor) const
{
	if (this->getGradeToExec() < executor.getGrade())
		throw GradeTooLowException(executor.getGrade(), EXEC);
	else if (this->getIsSigned() == false)
		throw FormNotSigned();
	else
	{
		std::string	noises[4];
		noises[0] = "BRRRRRRRRR!!!";
		noises[1] = "PTPTPTPTPTPT!!";
		noises[2] = "NYIIIIIIIIII!!!!!";
		noises[3] = "CLICK CLACK CLOCK";
		int	maxNoises = randomNumber(10);
		int pos = randomNumber(3);
		for (int i = 0; i < maxNoises; i++)
		{
			pos = randomNumber(3);
			std::cout << noises[pos] << std::endl;
			usleep(500000);
		}

		if (randomChance())
			std::cout << this->_target << " has been succesfully robotomized" << std::endl;
		else
			std::cout << "Robotomy failed!" << std::endl;
	}
}

/* ========== overload operator ==============*/
RobotomyRequestForm&	RobotomyRequestForm::operator=(RobotomyRequestForm const& other)
{
	(void)other;
	return *this;
}

