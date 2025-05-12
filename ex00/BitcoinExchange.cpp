/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:59:58 by bwach             #+#    #+#             */
/*   Updated: 2025/05/12 22:21:59 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"
#include <fstream>
#include <string>
#include <sstream>

//constructors and others:
ExchangeRate::ExchangeRate(): _Data(), _dataFileName(NULL) {}
ExchangeRate::ExchangeRate(const std::string& DataFile): _Data(), _dataFileName(DataFile) {}
ExchangeRate::ExchangeRate(ExchangeRate& other)
{
	*this = other;
}
ExchangeRate::~ExchangeRate() {}

ExchangeRate& ExchangeRate::operator=(const ExchangeRate& other)
{
	if (this != &other)
	{
		this->_Data = other._Data;
		this->_dataFileName = other._dataFileName;
	}
	return (*this);
}

//Public Method:
void	ExchangeRate::excecuteBtc(std::string& filePath, std::string& inputFile)
{
	loadData(filePath);
	processInputFile(inputFile);
}

//Private Methods:
void	ExchangeRate::loadData(const std::string& filePath)
{
	std::ifstream dataFile(filePath.c_str());
	if (!dataFile.is_open())
	{
		std::cerr << "Error: could not open file " << filePath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(dataFile, line))
	{
		if (line.empty()) // Skip empty lines
			continue;

		size_t delimiterPos = line.find(','); // Split the line into date and value
		if (delimiterPos == std::string::npos)
		{
			std::cerr << "Error: bad format in line => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, delimiterPos);
		std::string valueStr = line.substr(delimiterPos + 1);
		// Validate date and value
		if (!isValidDate(date))
		{
			std::cerr << "Error: invalid date in line => " << line << std::endl;
			continue;
		}
		if (!isValidValue(valueStr))
		{
			std::cerr << "Error: invalid value in line => " << line << std::endl;
			continue;
		}

		// Convert value to float using stringstream
		std::stringstream ss(valueStr);
		float value;
		if (!(ss >> value))
		{
			std::cerr << "Error: failed to parse value in line => " << line << std::endl;
			continue;
		}
		_Data[date] = value; // Insert into the map
	}
	dataFile.close();
}

void	ExchangeRate::processInputFile(const std::string& inputFile)
{
	std::ifstream dataFile(inputFile.c_str());
	if (!dataFile.is_open())
	{
		std::cerr << "Error: could not open file " << inputFile << std::endl;
		return;
	}

	std::string line;
	while (std::getline(dataFile, line))
	{
		if (line.empty()) // Skip empty lines
			continue;

		size_t delimiterPos = line.find(','); // Split the line into date and value
		if (delimiterPos == std::string::npos)
		{
			std::cerr << "Error: bad format in line => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, delimiterPos);
		std::string valueStr = line.substr(delimiterPos + 1);
		// Validate date and value
		if (!isValidDate(date))
		{
			std::cerr << "Error: invalid date in line => " << line << std::endl;
			continue;
		}
		if (!isValidValue(valueStr))
		{
			std::cerr << "Error: invalid value in line => " << line << std::endl;
			continue;
		}

		std::string	valueStr1 = valueStr;
		std::stringstream ss(valueStr1);
		float value;
		if (!(ss >> value))
		{
			std::cerr << "Error: failed to parse value in line => " << line << std::endl;
			continue;
		}

		float result = calculRate(date, value);
		displayResults(date, valueStr, result);
	}
	dataFile.close();
}

void	ExchangeRate::displayResults(const std::string& date, const std::string& value, float& res) const
{
	std::cout << date << " => " << value << " = " << res << std::endl;
}

//Private Methods:
bool	ExchangeRate::isValidDate(const std::string& date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int year, month, day;
	try
	{
		// Convertir les parties de la date en entiers
		std::stringstream yearStream(date.substr(0, 4));
		std::stringstream monthStream(date.substr(5, 2));
		std::stringstream dayStream(date.substr(8, 2));

		if (!(yearStream >> year) || !(monthStream >> month) || !(dayStream >> day))
			return false;
		if (month < 1 || month > 12 || day < 1 || day > 31)
			return false;
		//Verified if more than 30 days
		if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
			return false;
		//february and bisexxx
		if (month == 2)
		{
			bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
			if (day > (isLeap ? 29 : 28))
				return false;
		}
	}
	catch (...) //generique
	{
		return false;
	}
	return true;
}

bool ExchangeRate::isValidValue(const std::string& value) const
{
	std::stringstream ss(value);
	float floatValue;
	char remaining;

	if (!(ss >> floatValue) || (ss >> remaining))
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (floatValue < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (floatValue > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}