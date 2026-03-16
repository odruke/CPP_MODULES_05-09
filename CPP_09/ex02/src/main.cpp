#include <iostream>
#include <colors.hpp>
#include "MutantStack.hpp"
#include <list>
#include <stack>

/*============== helper funtion functions as a test for iteration =============*/
template<typename T, typename container>
void	printMutant(MutantStack<T, container>& mutant)
{
	for (MutantStack<unsigned int>::iterator it = mutant.begin(); it != mutant.end(); it++)
	{
		std::cout << "nº " << MAGENTA << *it << RESET;
		if (it + 1 !=  mutant.end())
			std::cout << ", ";
	}
	if (mutant.empty())
		std::cout << RED << "No numbers to show" << RESET;
	std::cout << ";" << std::endl;
}

int main()
{
/*============== test 0: subject example =============*/
	std::cout << YELLOW << "============== test 0: subject example =============" << RESET << std::endl;
	{
		MutantStack<int>	mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
	}


	std::cout << YELLOW << "============== return comparison with container <list> =============" << RESET << std::endl;
	{
		std::list<int>	mstack;
		mstack.push_back(5);
		mstack.push_back(17);
		std::cout << mstack.back() << std::endl;
		mstack.pop_back();
		std::cout << mstack.size() << std::endl;
		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		//[...]
		mstack.push_back(0);
		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int, std::list<int> > s(mstack);
		std::cout << YELLOW << "============== end of test 0 =============" << RESET << std::endl;
	}

/*============== test 1: stack methods =============*/
	std::cout << YELLOW << "\n============== test 1: stack methods =============" << RESET << std::endl;
	{
		MutantStack<unsigned int> ms;
		std::cout << YELLOW << "adding some numbers:" << RESET << std::endl;
		ms.push(1);
		ms.push(2);
		ms.push(3);
		printMutant(ms);
		std::cout << YELLOW << "\npop the last one" << RESET << std::endl;
		ms.pop();
		printMutant(ms);

/*============== test 2: iterate through the stack =============*/
	std::cout << YELLOW << "\n============== test 2: iterate through the stack =============" << RESET << std::endl;
		std::cout << YELLOW << "adding more numbers:" << RESET << std::endl;
		ms.push(3);
		ms.push(4);
		printMutant(ms);
		MutantStack<unsigned int>::iterator it = ms.begin();
		MutantStack<unsigned int>::iterator ite = ms.end();
		std::cout << "The begining of the stack is: " << MAGENTA << *it << RESET << std::endl;
		std::cout << "The end of the stack is: " << MAGENTA << *(ite - 1) << RESET << std::endl;
		ite--;
		std::cout << "The second to last of the stack is: " << MAGENTA << *(ite - 1) << RESET << std::endl;
	}
return 0;
}
