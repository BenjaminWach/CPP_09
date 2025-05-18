/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:06:07 by bwach             #+#    #+#             */
/*   Updated: 2025/05/18 23:23:06 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

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
	std::vector<int> tmp;
	this->_rangeSize = tmp.size();
	
	for (int i = 1; av[i] != NULL; ++i)
	{
		std::stringstream ss(av[i]);
		int a;
		if (!(ss >> a ) || a <= 0 || !ss.eof())
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
		tmp.push_back(a);
	}

	for (size_t i = 0; i < tmp.size(); i += 2)
	{
		int first = tmp[i];
		int second = (i + 1 < tmp.size()) ? tmp[i + 1] : -1;
		_Vec.push_back(std::make_pair(first, second));
		_Deq.push_back(std::make_pair(first, second));
	}
}

void	PmergeMe::fordJohnFSort(std::vector<std::pair<int, int> >& v)
{
	;
}

void	PmergeMe::fordJohnFSort(std::deque<std::pair<int ,int> >& d)
{
	;
}

//Public Method;
void	PmergeMe::execPmergeMe(char **av)
{
	//print Before:
	printBefore(av);

	//load:
	loadAllData(av);

	//Algo:
	clock_t start = clock();
	fordJohnFSort(this->_Vec);
	clock_t end = clock();
	double duration_vec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

	clock_t start = clock();
	fordJohnFSort(this->_Deq);
	clock_t end = clock();
	double duration_deq = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

	//print Chrono:
	std::cout << "Time to process a range of " << this->_rangeSize << " elements with std::vector" << duration_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << this->_rangeSize << " elements with std::deque" << duration_deq << " us" << std::endl;
}