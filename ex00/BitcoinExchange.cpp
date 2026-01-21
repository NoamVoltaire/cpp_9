#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <string>

bool	BitcoinExchange::set_btc_dataset(const char *path)
{
	//std::cout << path << std::endl;
	std::ifstream	file(path);
	if (!file.is_open())
	{
		std::cerr << "Error: cannot read from data.csv" << std::endl;
		return false;
	}

	std::string	line;

	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t	pos = line.find(",");
		if (pos == std::string::npos)
			continue;
		std::string	date = line.substr(0, pos - 1);
		std::string	valuestr = line.substr(pos + 1);

		double	value = std::atof(valuestr.c_str());
		data_set[date] = value;
	}
	std::cout << "THIS IS IT " << this->data_set.cbegin()->first << " and " << this->data_set.cbegin()->second << std::endl;
	//std::cout << "THIS IS IT " << this->data_set.begin()->first << this->data_set.begin()->second << std::endl;

	file.close();
	return true;
}

BitcoinExchange::BitcoinExchange()
{
	if (!set_btc_dataset("data.csv"))
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

bool	valid_date(const std::string &date_str)
{
	if (date_str.length() != 10)
		return false;
	return true;
}


void	BitcoinExchange::fromFile(const char *input_file)
{

	std::ifstream	file(input_file);
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	std::string	line;

	while (std::getline(file, line))
	{
		size_t	pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line <<std::endl;
			continue;
		}
		std::string	date = line.substr(0, pos - 1);
		std::string	nb = line.substr(pos + 3);
		
		if (!valid_date(date))
		{

		}

	}


	//
}
