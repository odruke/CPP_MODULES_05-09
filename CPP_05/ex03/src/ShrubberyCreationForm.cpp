#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

/* ========== Constructors and destructor ==============*/

ShrubberyCreationForm::ShrubberyCreationForm(std::string const& target)
: AForm("ShrubberyCreationForm",  145, 137),  _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const& copy)
: AForm("ShrubberyCreationForm", copy.getGradeToSign(), copy.getGradeToExec()), _target(copy._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

/* ========== member functions ==============*/
void	ShrubberyCreationForm::execute(Bureaucrat const& executor) const
{
	if (executor.getGrade() > this->getGradeToExec())
		throw GradeTooLowException(executor.getGrade(), EXEC);
	else if (this->getIsSigned() == false)
		throw FormNotSigned();
	else
	{
		std::string	filename = this->_target + "_shrubbery";
		std::ofstream outfile(filename.c_str());

		for (int i = 0; i < 5; i++)
		{
			outfile <<\
					"		                      ___\n\
									_,-\'\"\"   \"\"\"\"`--.\n\
								,-\'          __,,-- \n\
							,\'    __,--\"\"\"\"dF      )\n\
							/   .-\"Hb_,--\"\"dF      /\n\
							,\'       _Hb ___dF\"-._,-\'\n\
						,\'      _,-\"\"\"\"   \"\"--..__\n\
						(     ,-\'                  `.\n\
						`._,\'     _   _             ;\n\
						,\'     ,\' `-\'Hb-.___..._,-\'\n\
						\\    ,\'\"Hb.-\'HH`-.dHF\"\n\
							`--\'   \"Hb  HH  dF\"\n\
									\"Hb HH dF\n\
									\"HbHHdF\n\
									|HHHF\n\
									|HHH|\n\
									|HHH|\n\
									|HHH|\n\
									|HHH|\n\
									dHHHb\n\
									.dFd|bHb.               o\n\
						o       .dHFdH|HbTHb.          o /\n\
					\\  Y  |  \\__,dHHFdHH|HHhoHHb.__Krogg  Y\n\
					##########################################\n" << std::endl;
		}
		outfile.close();
	}
}

/* ========== overload operator ==============*/
ShrubberyCreationForm&	ShrubberyCreationForm::operator=(ShrubberyCreationForm const& other)
{
	(void)other;
	//constant members can only be assigned at initialization
	//other than _isSigned will remain unchanged
	return *this;
}


