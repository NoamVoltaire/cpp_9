#include "RPN.hpp"
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other) { *this = other; }

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		// Copy members here
	}
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

	int	res = 0;
	int	a;
	int	b;

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
				std::cerr << "Error: division by 0" << std::endl;
				throw std::runtime_error("division by 0");
			}
			res = a / b;
			break;
		}
	}
	this->stack.push(res);
}



int	RPN::calculate(const std::string &sequence)
{
	std::stringstream	stream;
	std::string		token;

	stream << sequence;
	while (stream >> token)
	{
		if (token.size() != 1 || (!std::isdigit(token[0]) && !is_operator(token[0])))
		{
			std::cerr << "Error : only accepts single digit and + - * / " <<  std::endl;
			return -1;
		}
		if (std::isdigit(token[0]))
			stack.push(token[0] - '0');
		else if (stack.size() < 2)
		{
			std::cerr << "Error : sequence has not enough numbers" <<  std::endl;
			return -1;
		}
		else
		{
			try
			{
				do_operation(token[0]);
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() <<  std::endl;
				return -1;
			}

		}
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error : sequence has not enough operator" <<  std::endl;
		return -1;
	}
	std::cout << stack.top() << std::endl;
	return stack.top();

}
