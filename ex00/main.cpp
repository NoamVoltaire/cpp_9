#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		BitcoinExchange	btc_exchgr;

		btc_exchgr.fromFile(av[1]);


	}
}
