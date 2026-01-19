#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>

bool	BitcoinExchange::set_btc_dataset(const char *path)
{
	std::ifstream	file;
	if (file.is_open())
		return false;


	return true;
}


BitcoinExchange::BitcoinExchange()
{
	if (set_btc_dataset("data.csv"))
		std::cerr << "uh oh"  << std::endl;
		//throw error;
	std::cout << "BitcoinExchange: Default constructor called" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "BitcoinExchange: Destructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	std::cout << "BitcoinExchange: Copy constructor called" << std::endl;
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	std::cout << "BitcoinExchange: Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		// Copy members here
	}
	return *this;
}


//BitcoinExchange::BitcoinExchange(const std::string &input_file)
//{

	//see first data base
	//fill map
	//see input file
	//

//}

void	BitcoinExchange::fromFile(const std::string &input_file)
{
	//
}
