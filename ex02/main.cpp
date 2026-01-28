#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error : need arg(s)" << std::endl;
		return 1;
	}
	av++;
	PmergeMe	pmerge(ac - 1, av);
}
