#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>

bool	BitcoinExchange::set_btc_dataset(const char *path)
{
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
		std::string	date = line.substr(0, pos);
		std::string	valuestr = line.substr(pos + 1);

		float	value = std::atof(valuestr.c_str());
		data_set[date] = value;
	}
	file.close();
	return true;
}

BitcoinExchange::BitcoinExchange()
{
	if (!set_btc_dataset("data.csv"))
		throw std::runtime_error("Error : data.csv is not valid") ;
}

BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { *this = other; }

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->data_set = other.data_set;
	}
	return *this;
}


std::map<std::string, float>::const_iterator	BitcoinExchange::find_date_or_lower(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = data_set.lower_bound(date);

	if (it != data_set.end() && it->first == date)
		return (it);
	else if (it == data_set.begin())	//	if true it means that date lower than what exist
		it = data_set.end();
	else
		--it;
	return (it);

}


float	BitcoinExchange::exchanger(const std::string &date, const char *value) const
{
	std::map<std::string, float>::const_iterator it = find_date_or_lower(date);
	
	if (it == data_set.end())
		return (-1);
	else
		return (it->second * std::strtof(value, NULL));
}

static bool	valid_value(const std::string &value_str)
{
	int	dot = 0;
	size_t	i;

	(value_str[0] == '+' || value_str[0] == '-') ? i = 1 : i = 0;
	while (i < value_str.length())
	{
		if (!std::isdigit(value_str[i]))
		{
			if (value_str[i] == '.' && dot < 1)
				dot++;
			else 
			{
				std::cerr << "Error: invalid number format => " << value_str << std::endl;
				return false;
			}
		}
		i++;
	}

	errno = 0;
	float	nb = std::strtof(value_str.c_str(), NULL);
	if (nb < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (errno == ERANGE || nb > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
	
}

static bool	valid_date(const std::string &date_str)
{
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

	if (day > 31 || month > 12 || month < 1 || day < 1)
		return false;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day == 31)
			return false;
	if (month == 2)
	{
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
	size_t		index = -1;

	while (std::getline(file, line))
	{
		++index;
		if (line == "date | value" && index == 0)
			continue;
		size_t	pos = line.find(" | ");
		if (pos == std::string::npos || line.length() < 14)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string	date = line.substr(0, pos);
		std::string	value = line.substr(pos + 3);
		
		if (!valid_date(date))
		{
			std::cerr << "Error: invalid date => " << date << std::endl;
			continue;
		}
		if (!valid_value(value))
			continue;
		float	result = exchanger(date, value.c_str());
		if (result < 0)
		{
			std::cerr << "Error: no date that early => " << date << std::endl;
			continue;
		}
		else
			std::cout << date << " => " << value << " = " << result << std::endl;

	}


	//
}
