#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange	btc_exchgr;
	if (ac == 2)
		btc_exchgr.fromFile(av[1]);
	else
		std::cerr << "Error: could not open file." << std::endl;
}
