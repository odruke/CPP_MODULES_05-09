#include "RPN.hpp"

/*======================= CONSTRUCTOR AND DESTRUCTOR ============================*/

RPN::RPN(void) : _stack(), _solution("0") {}
RPN::RPN(std::string const& expression)
{
	size_t badToken = expression.find_first_not_of("0123456789 -+*/");
	if ( badToken != std::string::npos)
	{
		char bad = expression.at(badToken);
		throw ERROR_EXCPT(std::string("bad token: ") + bad);
	}

	this->_solution = this->_processExpression(expression);

}

RPN::RPN(RPN const& copy) : _stack(copy._stack), _solution(copy._solution){}

RPN::~RPN(void) {}

/*======================== ASSING OPERATOR =============================================*/

RPN&	RPN::operator=(RPN const& other)
{
	if (this == &other)
		return *this;
	this->_stack = other._stack;
	this->_solution = other._solution;

	return *this;
}

/*========================= PRIVATE FUNCTIONS =====================================================*/

//OPERATORS
void	RPN::_add(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	RPN::BigInt	b = this->_stack.top();
	this->_stack.pop();
	RPN::BigInt	a = this->_stack.top();
	this->_stack.pop();

	RPN::BigInt result = a + b;
	this->_stack.push(result);
}

void	RPN::_substract(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	RPN::BigInt	b = this->_stack.top();
	this->_stack.pop();
	RPN::BigInt	a = this->_stack.top();
	this->_stack.pop();

	RPN::BigInt result = a - b;
	this->_stack.push(result);
}

void	RPN::_multiply(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	RPN::BigInt	b = this->_stack.top();
	this->_stack.pop();
	RPN::BigInt	a = this->_stack.top();
	this->_stack.pop();

	RPN::BigInt result = a * b;
	this->_stack.push(result);
}

void	RPN::_divide(void)
{
	if (this->_stack.size() < 2)
		throw ERROR_EXCPT("Bad token: not enought numbers in the stack to operate");

	RPN::BigInt	b = this->_stack.top();
	this->_stack.pop();
	RPN::BigInt	a = this->_stack.top();
	this->_stack.pop();

	RPN::BigInt zero("0");

	if (b == zero)
		throw ERROR_EXCPT("Can not divide by 0");

	RPN::BigInt result = a / b;
	this->_stack.push(result);
}

//PROCESS
std::string	RPN::_processExpression(std::string const& expresssion)//pointer over function
{
	//1.add a token to the stack
	//first 2 token must be number, we can check stack size
	//after each number or operator must be space
	//if operator extract call operation function. We have to check stack size if not min 2 throw
	//operator function extracts 2 last tokens, operates, and stores result

	std::string operators = "+-*/";
	void	(RPN::*operation[operators.size()])() = {&RPN::_add, &RPN::_substract, &RPN::_multiply, &RPN::_divide};

	bool	expectSpace = false;
	bool	negative = false;
	char	token = expresssion.at(0);

	for (size_t i = 0; i < expresssion.size(); i++)
	{
		token = expresssion.at(i);

		if (std::isdigit(token))
		{
			if (expectSpace)
				throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

			std::string tokenStr(1, token);

			if (negative)
			{
				std::string minus("-");
				minus.append(tokenStr);
				tokenStr = minus;
				negative = false;
			}

			BigInt	num(tokenStr);
			this->_stack.push(num);
			expectSpace = true;
		}
		else if (token == ' ')
		{
			if (!expectSpace || i + 1 == expresssion.size())
				throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

			expectSpace = false;
		}
		else
		{
			if (expectSpace || operators.find(token) == std::string::npos)
				throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

			if (token == '-' && expresssion[i + 1] && expresssion[i + 1] != ' ')
			{
				negative = true;
				continue;
			}

			for (size_t j = 0; j < operators.size(); j++)
			{
				if (operators.at(j) == token)
				{
					(this->*operation[j])();
					break;
				}
			}

			expectSpace = true;
		}
	}

	if (this->_stack.size() != 1)
		throw ERROR_EXCPT(std::string("Unexpected token: ") + token);

	std::ostringstream oss;
	oss << this->_stack.top();

	return oss.str();
}

/*========================== PUBLIC FUNCTIONS =======================================================*/

void	RPN::printSolution(void)
{
	std::cout << this->_solution << std::endl;
}


/*======================== EXCEPTIONS =============================================*/

RPN::errorExcept::errorExcept(std::string const& file, int line, std::string msg)
{
	if (DEBUG)
	{
		std::ostringstream oss;
		oss << RED << "Error at: " << RESET
		<< file  << ":" << line << "\n"
		<< RED << msg;
		this->_msg = oss.str();
	}
	else
		this->_msg =  "Error";

}

RPN::errorExcept::~errorExcept(void) throw() {}

const char* RPN::errorExcept::what(void) const throw()
{
	return this->_msg.c_str();
}


/*====================== BIGINT CLASS ============================================*/

RPN::BigInt::BigInt(std::string const& num)
{
	if (num.empty())
		throw std::invalid_argument("BigInt: empty input");

	size_t start = 0;
	this->_isNegative = false;

	if (num[0] == '+' || num[0] == '-')
	{
		this->_isNegative = (num[0] == '-');
		start = 1;
	}

	if (start == num.size())
		throw std::invalid_argument("BigInt: invalid input");

	for (size_t i = start; i < num.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(num[i])))
			throw std::invalid_argument("BigInt: invalid input");
	}

	this->_num = num.substr(start);
	this->_normalize();
}

RPN::BigInt::BigInt(BigInt const& copy)
	: _num(copy._num), _isNegative(copy._isNegative) {}

RPN::BigInt&	RPN::BigInt::operator=(BigInt const& other)
{
	if (this == &other)
		return *this;

	this->_num = other._num;
	this->_isNegative = other._isNegative;
	return *this;
}

RPN::BigInt::~BigInt(void) {}

void	RPN::BigInt::_normalize(void)
{
	size_t firstNonZero = this->_num.find_first_not_of('0');
	if (firstNonZero == std::string::npos)
	{
		this->_num = "0";
		this->_isNegative = false;
		return;
	}
	if (firstNonZero > 0)
		this->_num.erase(0, firstNonZero);
}

std::string	RPN::BigInt::getNum(void) const
{
	if (this->_isNegative)
		return "-" + this->_num;
	return this->_num;
}

//comparison

int	RPN::BigInt::_compareAbs(std::string const& a, std::string const& b) const
{
	if (a.size() < b.size())
		return -1;
	if (a.size() > b.size())
		return 1;

	if (a == b)
		return 0;

	for (size_t i = 0; i < a.size(); ++i)
	{
		if (a[i] < b[i])
			return -1;
		if (a[i] > b[i])
			return 1;
	}

	return 0;
}

bool RPN::BigInt::operator==(BigInt const& other) const
{
	return this->_isNegative == other._isNegative && this->_num == other._num;
}

bool RPN::BigInt::operator!=(BigInt const& other) const
{
	return !(*this == other);
}

bool RPN::BigInt::operator<(BigInt const& other) const
{
	if (this->_isNegative != other._isNegative)
		return this->_isNegative;

	int cmp = this->_compareAbs(this->_num, other._num);
	if (this->_isNegative)
		return cmp > 0;
	return cmp < 0;
}

bool RPN::BigInt::operator>(BigInt const& other) const
{
	return other < *this;
}

bool RPN::BigInt::operator<=(BigInt const& other) const
{
	return !(*this > other);
}

bool RPN::BigInt::operator>=(BigInt const& other) const
{
	return !(*this < other);
}

//aritmetics
std::string	RPN::BigInt::_addAbs(std::string const& a, std::string const& b) const
{
	int idxA = static_cast<int>(a.size()) - 1;
	int idxB = static_cast<int>(b.size()) - 1;
	std::string result;
	int carry = 0;

	while (idxA >= 0 || idxB >= 0 || carry > 0)
	{
		int digitA = 0;
		if (idxA >= 0)
			digitA = a[idxA] - '0';

		int digitB = 0;
		if (idxB >= 0)
			digitB = b[idxB] - '0';

		int sum = digitA + digitB + carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');

		idxA--;
		idxB--;
	}
	std::reverse(result.begin(), result.end());

	return result;
}

std::string	RPN::BigInt::_subAbs(std::string const& a, std::string const& b) const
{
	int idxA = static_cast<int>(a.size()) - 1;
	int idxB = static_cast<int>(b.size()) - 1;
	int borrow = 0;
	std::string result;

	while (idxA >= 0)
	{
		int digitA = (a[idxA] - '0') - borrow;
		int digitB = 0;
		if (idxB >= 0)
			digitB = b[idxB] - '0';

		if (digitA < digitB)
		{
			digitA += 10;
			borrow = 1;
		}
		else
			borrow = 0;

		result.push_back((digitA - digitB) + '0');
		idxA--;
		idxB--;
	}

	while (result.size() > 1 && result[result.size() - 1] == '0')
		result.erase(result.size() - 1);

	std::reverse(result.begin(), result.end());
	return result;
}

std::string	RPN::BigInt::_mulAbs(std::string const& a, std::string const& b) const
{
	if (a == "0" || b == "0")
		return "0";

	size_t resultSize = a.size() + b.size();
	int* result = new int[resultSize];
	for (size_t i = 0; i < resultSize; ++i)
		result[i] = 0;

	for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
	{
		for (int j = static_cast<int>(b.size()) - 1; j >= 0; --j)
		{
			int mul = (a[i] - '0') * (b[j] - '0');
			int sum = mul + result[i + j + 1];
			result[i + j + 1] = sum % 10;
			result[i + j] += sum / 10;
		}
	}

	std::string out;
	size_t first = 0;
	while (first < resultSize && result[first] == 0)
		++first;

	for (; first < resultSize; ++first)
		out.push_back(static_cast<char>('0' + result[first]));

	delete[] result;

	if (out.empty())
		return "0";
	return out;
}

std::string	RPN::BigInt::_divAbs(std::string const& a, std::string const& b) const
{
	if (b == "0")
		throw std::runtime_error("BigInt: division by zero");
	if (a == "0" || this->_compareAbs(a, b) < 0)
		return "0";

	std::string quotient;
	std::string remainder("0");

	for (size_t i = 0; i < a.size(); ++i)
	{
		if (remainder == "0")
			remainder = std::string(1, a[i]);
		else
			remainder.push_back(a[i]);

		size_t pos = remainder.find_first_not_of('0');
		if (pos == std::string::npos)
			remainder = "0";
		else if (pos > 0)
			remainder.erase(0, pos);

		int qDigit = 0;
		std::string product("0");
		for (int d = 9; d >= 1; --d)
		{
			std::string digit(1, static_cast<char>('0' + d));
			std::string test = this->_mulAbs(b, digit);
			if (this->_compareAbs(test, remainder) <= 0)
			{
				qDigit = d;
				product = test;
				break;
			}
		}

		quotient.push_back(static_cast<char>('0' + qDigit));
		if (qDigit != 0)
			remainder = this->_subAbs(remainder, product);
	}

	size_t firstNonZero = quotient.find_first_not_of('0');
	if (firstNonZero == std::string::npos)
		return "0";
	return quotient.substr(firstNonZero);
}

RPN::BigInt	RPN::BigInt::operator+(BigInt const& other)
{
	std::string absResult;
	bool negativeResult = false;

	if (this->_isNegative == other._isNegative)
	{
		absResult = this->_addAbs(this->_num, other._num);
		negativeResult = this->_isNegative;
	}
	else
	{
		int cmp = this->_compareAbs(this->_num, other._num);
		if (cmp == 0)
			return RPN::BigInt("0");
		if (cmp > 0)
		{
			absResult = this->_subAbs(this->_num, other._num);
			negativeResult = this->_isNegative;
		}
		else
		{
			absResult = this->_subAbs(other._num, this->_num);
			negativeResult = other._isNegative;
		}
	}

	if (absResult == "0")
		negativeResult = false;
	if (negativeResult)
		return RPN::BigInt("-" + absResult);
	return RPN::BigInt(absResult);
}

RPN::BigInt	RPN::BigInt::operator-(BigInt const& other)
{
	std::string absResult;
	bool negativeResult = false;

	if (this->_isNegative != other._isNegative)
	{
		absResult = this->_addAbs(this->_num, other._num);
		negativeResult = this->_isNegative;
	}
	else
	{
		int cmp = this->_compareAbs(this->_num, other._num);
		if (cmp == 0)
			return RPN::BigInt("0");
		if (cmp > 0)
		{
			absResult = this->_subAbs(this->_num, other._num);
			negativeResult = this->_isNegative;
		}
		else
		{
			absResult = this->_subAbs(other._num, this->_num);
			negativeResult = !this->_isNegative;
		}
	}

	if (absResult == "0")
		negativeResult = false;
	if (negativeResult)
		return RPN::BigInt("-" + absResult);
	return RPN::BigInt(absResult);
}

RPN::BigInt	RPN::BigInt::operator*(BigInt const& other)
{
	std::string absResult = this->_mulAbs(this->_num, other._num);
	bool negativeResult = (this->_isNegative != other._isNegative);

	if (absResult == "0")
		negativeResult = false;
	if (negativeResult)
		return RPN::BigInt("-" + absResult);
	return RPN::BigInt(absResult);
}

RPN::BigInt	RPN::BigInt::operator/(BigInt const& divisor)
{
	if (divisor._num == "0")
		throw std::runtime_error("BigInt: division by zero");

	std::string absResult = this->_divAbs(this->_num, divisor._num);
	bool negativeResult = (this->_isNegative != divisor._isNegative);

	if (absResult == "0")
		negativeResult = false;
	if (negativeResult)
		return RPN::BigInt("-" + absResult);
	return RPN::BigInt(absResult);
}


std::ostream&	operator<<(std::ostream &os, RPN::BigInt Num)
{
	os << Num.getNum();

	return os;
}
