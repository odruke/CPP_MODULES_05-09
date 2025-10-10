#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "colors.hpp"
#include <ctime>
#include <cstdlib>

int randomNumber(int max)
{
	static bool seeded = false;

	if (!seeded) {
		srand(time(NULL));
		seeded = true;
	}
	return rand() % (max + 1);
}

Base*	generate(void)
{
	int i = randomNumber(2);
	if (i == 0)
		return new A;
	if (i == 1)
		return new B;
	if (i == 2)
		return new C;
	return NULL;
}
void identify(Base* p)
{
	A* a = dynamic_cast<A*>(p);
	B* b = dynamic_cast<B*>(p);
	C* c = dynamic_cast<C*>(p);

	std::string realClass = a != NULL ? "A" : (b != NULL? "B" : (c != NULL? "C" : "unknown"));
	std::cout << "i'm a pointer to class " << GREEN << realClass << RESET << std::endl;
}

void identify(Base& p)
{
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "i'm a reference to class "
				<< GREEN << "A" << RESET << std::endl;
	}catch(const std::exception &e){}
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "i'm a reference to class "
				<< GREEN << "B" << RESET << std::endl;
	}catch(const std::exception &e) {}
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "i'm a reference to class "
				<< GREEN << "C" << RESET << std::endl;
	}catch(const std::exception &e) {}
}

int	main()
{
	Base*	misteryClass = generate();
	identify(misteryClass);
	identify(*misteryClass);

	delete misteryClass;
}
