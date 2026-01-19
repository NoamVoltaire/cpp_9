#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <stdbool.h>

class BitcoinExchange
{
private:
	std::map<std::string, double> data_set;

	bool	set_btc_dataset(const char *path);
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);


	//BitcoinExchange(const std::string &input_file);
	void	fromFile(const std::string &input_file);
	
};

#endif
