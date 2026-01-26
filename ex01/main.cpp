#include "RPN.hpp"
#include <cctype>
#include <sstream>

int	main(int ac, char **av)
{
	RPN	rpn;

	if (ac ==2)
	{
		rpn.calculate(av[1]);
	}
	else
	{
		std::cerr << "Error : only accepts 1 arg" << std::endl;
		return 1;
	}

}
