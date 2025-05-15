/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:59:54 by bwach             #+#    #+#             */
/*   Updated: 2025/05/14 17:51:21 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <algorithm>

class ExchangeRate
{
	public:
			ExchangeRate();
			ExchangeRate(const std::string& inputFile);
			ExchangeRate(ExchangeRate& other);
			~ExchangeRate();

			ExchangeRate& operator=(const ExchangeRate& other);
			
			void	excecuteBtc(std::string& filePath, std::string& inputFile);
			
	private:
			std::string _InputFile;
			std::map<std::string, float> _Data;
			
			bool	isValidDate(const std::string& date) const;
			bool	isValidValue(std::string& value) const;

			void	loadData(const std::string& filePath); //load the data into map
			void	processInputFile(const std::string& inputFile); //read, validate
			float	calculValue(const std::string& date, float& value) const;
			void	displayResults(const std::string& date, const std::string& value, float& res) const;
};