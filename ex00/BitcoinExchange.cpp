#include "BitcoinExchange.hpp"
#include <cctype>
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
	//std::cout << "string = " << date_str << std::endl;
	if (date_str.length() != 10)
		return false;
	std::string::size_type	posym = date_str.find_first_of("-");
	std::string::size_type	posmd = date_str.find_last_of("-");
	if (posym == std::string::npos || posym == posmd)  
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date_str[i]))
			return false;
	}

	int	year = std::atoi(date_str.substr(0, posym).c_str());
	int	month = std::atoi(date_str.substr(posym + 1, posmd).c_str());
	int	day = std::atoi(date_str.substr(posmd + 1).c_str());

	//std::cout << year << " "<< month << " " <<  day << std::endl;
	if (day > 31 || month > 12 || month < 1 || day < 1)
		return false;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day == 31)
			return false;
	if (month == 2)
	{
		//if (!(year % 4) && (year % 100) && !(year % 400))
		//if (((year % 400) && (year %100)) && !(year % 4)) 
		if (!(year % 400) || (!(year % 4) && (year % 100)))
		{
			if (day > 29)
				return false;
		}
		else
		{
			if (day > 28)
				return false;
		}
	}
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
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t	pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line <<std::endl;
			continue;
		}
		std::string	date = line.substr(0, pos);
		std::string	nb = line.substr(pos + 3);
		
		if (!valid_date(date))
		{

			std::cerr << "Error: invalid date =>" << date <<std::endl;
			continue;
		}

	}


	//
}
