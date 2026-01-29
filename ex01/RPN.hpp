#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <list>

class RPN
{
private:
	std::stack<int, std::list<int> > stack;
public:
	RPN();
	~RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);

	bool	calculate(const std::string &sequence);
	void	do_operation(const char &op);
};

#endif
