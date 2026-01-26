#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <stdbool.h>

class BitcoinExchange
{
private:
	std::map<std::string, float> data_set;

	bool	set_btc_dataset(const char *path);
	float	exchanger(const std::string &date, const char *value) const;
	std::map<std::string, float>::const_iterator	find_date_or_lower(const std::string &date) const;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);


	//BitcoinExchange(const std::string &input_file);
	void	fromFile(const char *input_file);
	
};

#endif
