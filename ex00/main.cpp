/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:59:04 by bwach             #+#    #+#             */
/*   Updated: 2025/05/14 18:20:33 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open the file" << std::endl;
		return (1);
	}
	
	ExchangeRate btc;

	std::string dataFile = "data.csv";
	std::string inputFile = argv[1];
	btc.excecuteBtc(dataFile, inputFile);

	return (0);
}