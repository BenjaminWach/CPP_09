/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:59:58 by bwach             #+#    #+#             */
/*   Updated: 2025/06/04 16:10:14 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"
#include <fstream>
#include <string>
#include <sstream>

//constructors and others:
ExchangeRate::ExchangeRate(): _InputFile("") {}
ExchangeRate::ExchangeRate(const std::string& inputFile): _InputFile(inputFile) {}
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
		this->_InputFile = other._InputFile;
	}
	return (*this);
}

//Public Method:
void	ExchangeRate::excecuteBtc(std::string& filePath, std::string& inputFile)
{
	// std::cout << "filePath: " << filePath << std::endl;
	// std::cout << "inputFile: " << inputFile << std::endl;
	loadData(filePath);
	processInputFile(inputFile);
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

bool ExchangeRate::isValidValue(std::string& value) const
{
	//cut the potential extra
	size_t cut = value.find_first_not_of("0123456789.-");
	if (cut != std::string::npos)
		value = value.substr(0, cut);

	std::stringstream ss(value);
	float floatValue;
	ss >> floatValue;

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


//Load the CSV data to the map
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
		std::string rateStr = line.substr(delimiterPos + 1);
		// Validate date and value
		if (!isValidDate(date))
		{
			continue;
		}
		// Convert rate to float using stringstream
		std::stringstream ss(rateStr);
		float rate;
		if (!(ss >> rate))
		{
			std::cerr << "Error: failed to parse value in line => " << line << std::endl;
			continue;
		}
		_Data[date] = rate; // Insert into the map
		//_Data.insert(std::make_pair(date, rate)); //permet d'eviter d'ecraser un taux deja present
	}
	dataFile.close();
}

//Read the input text file and execute
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

		if (line.find("date | value") != std::string::npos) //if find "..." skip
			continue;

		size_t delimiterPos = line.find('|');
		if (delimiterPos == std::string::npos) //if not found
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		//cut the line into date and value
		std::string date = line.substr(0, delimiterPos);
		std::string valueStr = line.substr(delimiterPos + 1);

		//trim the space infront and behind
		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

		// Validate date and value
		if (!isValidDate(date))
		{
			std::cerr << "Error: invalid date => " << date << std::endl;
			continue;
		}
		if (!isValidValue(valueStr))
			continue;

		std::string	valueStr1 = valueStr;
		std::stringstream ss(valueStr1);
		float value;
		if (!(ss >> value))
		{
			std::cerr << "Error: failed to parse value in line => " << line << std::endl;
			continue;
		}

		float result = calculValue(date, value);
		displayResults(date, valueStr, result);
	}
	dataFile.close();
}

float	ExchangeRate::calculValue(const std::string& date, float& value) const
{
	//iterator to the first element of map that the key isnt inferior to the date
	//if date exist, it point to
	//if not it point to the superior date on the pile;
	std::map<std::string, float>::const_iterator it = _Data.lower_bound(date);

	if (it == _Data.end() || it->first != date)
	{
		if (it == _Data.begin())
		{
			std::cerr << "Error: no rate available for this date or before => " << date << std::endl;
			return (0.0f);
		}
		--it;
	}
	return (value * it->second);
}

void	ExchangeRate::displayResults(const std::string& date, const std::string& value, float& res) const
{
	std::cout << date << " => " << value << " = " << res << std::endl;
}
