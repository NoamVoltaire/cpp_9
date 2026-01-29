#include "RPN.hpp"
#include <limits>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other) { *this = other; }

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		this->stack = other.stack;
	return *this;
}


static	bool	is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/') 
		return true;
	return false;
}

void	RPN::do_operation(const char &op)
{

	long	res = 0;
	long	a;
	long	b;

	b = stack.top();
	stack.pop();
	a = stack.top();
	stack.pop();

	switch(op)
	{
		case '+':
			res = a + b;
			break;
		case '-':
			res = a - b;
			break;
		case '*':
			res = a * b;
			break;
		case '/':
		{
			if (b == 0)
			{
				//std::cerr << "Error: division by 0" << std::endl;
				throw std::runtime_error("division by 0");
			}
			res = a / b;
			break;
		}
	}
	if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min())
		throw std::runtime_error("int overflow");
	this->stack.push(res);
}



bool	RPN::calculate(const std::string &sequence)
{
	std::stringstream	stream;
	std::string		token;

	stream << sequence;
	while (stream >> token)
	{
		if (token.size() != 1 || (!std::isdigit(token[0]) && !is_operator(token[0])))
		{
			std::cerr << "Error: only accepts single digit and + - * / " <<  std::endl;
			return false;
		}
		if (std::isdigit(token[0]))
			stack.push(token[0] - '0');
		else if (stack.size() < 2)
		{
			std::cerr << "Error: sequence has not enough numbers" <<  std::endl;
			return false;
		}
		else
		{
			try
			{
				do_operation(token[0]);
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error: "<< e.what() <<  std::endl;
				return false;
			}

		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error: sequence has not enough operator" <<  std::endl;
		return false;
	}
	std::cout << stack.top() << std::endl;
	return true;
}
