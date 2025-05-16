/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:06:07 by bwach             #+#    #+#             */
/*   Updated: 2025/05/16 18:12:07 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//Constructors && desctructor
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& rhn)
{
	*this = rhn;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_Vec = other._Vec;
		this->_Deq = other._Deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

//Private Methods
void	PmergeMe::printBefore(char **av)
{
	std::cout << "Before: ";
	for (int i = 1; av[i]; ++i)
		std::cout << av[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::loadAllData(char **av)
{
	;
}

//Public Method;
void	PmergeMe::execPmergeMe(char **av)
{
	//print Before:
	printBefore(av);

	//load
	loadAllData(av);
	
	//algo
	//print chrono
	//print After
}