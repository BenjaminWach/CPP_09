/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:06:07 by bwach             #+#    #+#             */
/*   Updated: 2025/05/27 02:06:03 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

Pair::Pair() {}
Pair::Pair(const Pair& rhn)
{
	*this = rhn;
}
Pair& Pair::operator=(const Pair& other)
{
	if (this != &other)
	{
		this->winner = other.winner;
		this->loser = other.loser;
		this->winnerInd = other.winnerInd;
	}
	return *this;
}
Pair::~Pair() {}

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
		this->_listV = other._listV;
		this->_listDeq = other._listDeq;
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

void	PmergeMe::printAfterV(const std::vector<int>& sorted)
{
	std::cout << "After: ";
	for (size_t i = 0; i < sorted.size(); ++i)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;
}

void	PmergeMe::loadAllData(char **av)
{
	this->_listV.clear();
	this->_listDeq.clear();
	
	for (int i = 1; av[i] != NULL; ++i)
	{
		std::stringstream ss(av[i]);
		int a;
		if (!(ss >> a ) || a <= 0 || !ss.eof())
		{
			std::cerr << "Error" << std::endl;
			exit(1);
		}
		_listV.push_back(a);
		_listDeq.push_back(a);
	}

	if (this->_listV.size() != this->_rangeSize || this->_listDeq.size() != this->_rangeSize)
	{
		std::cerr << "Error: container size mismatch" << std::endl;
		exit(1);
	}
}

/*######################################################################################*/
static void	recursiveSort(std::vector<int>& sortedWinner, std::vector<Pair>& p)
{
	if (p.size() == 1)
	{
		sortedWinner.push_back(p[0].winner);
		return;
	}

	//extract winners from vector pairs
	std::vector<int> winners;
	for (size_t i = 0; i < p.size(); ++i)
		winners.push_back(p[i].winner);
	
	//cut the list in two
	size_t mid = winners.size() / 2;
	std::vector<int> left, right;
	for (size_t i = 0; i < mid; ++i) left.push_back(winners[i]);
	for (size_t i = mid; i < winners.size(); ++i) right.push_back(winners[i]);

	//recursive
	std::vector<int> sortedLeft, sortedRight;
	std::vector<Pair> leftPairs(p.begin(), p.begin() + mid);
	std::vector<Pair> rightPairs(p.begin() + mid, p.end());
	if (!left.empty()) recursiveSort(sortedLeft, leftPairs);
	if (!right.empty()) recursiveSort(sortedRight, rightPairs);

	//fuze left and right
	size_t i = 0;
	size_t j = 0;
	while (i < sortedLeft.size() && j < sortedRight.size())
	{
		if (sortedLeft[i] < sortedRight[j])
			sortedWinner.push_back(sortedLeft[i++]);
		else
			sortedWinner.push_back(sortedRight[j++]);
	}
	while (i < sortedLeft.size()) sortedWinner.push_back(sortedLeft[i++]);
	while (j < sortedRight.size()) sortedWinner.push_back(sortedRight[j++]);
}

static	void	jacobsthalBinary(std::vector<int>& sortedWinner, std::vector<Pair>& pairs)
{
	//generate jacobsthal sequence:
	//J(0) = 0 / J(1) = 1 / J(n) = J(n - 1) + 2*J(n - 2);
	std::vector<size_t> jacobsthal;
	size_t nbPairs = pairs.size();
	jacobsthal.push_back(1);
	while (jacobsthal.back() < nbPairs)
	{
		size_t tmp = jacobsthal.size();
		size_t next = tmp > 1 ? jacobsthal[tmp - 1]
			+ 2*jacobsthal[tmp - 2] : 1;
		if (next < nbPairs)
			jacobsthal.push_back(next);
		else
			break;
	}

	for (size_t x = 0; x < jacobsthal.size(); ++x)
	{
		size_t i = jacobsthal[x];
		if (i >= pairs.size())
			continue;
		if (pairs[i].loser == -1)
			continue;
		if (pairs[i].loserInserted == true)
			continue;

		size_t winnerPos = pairs[i].winnerInd;

		//Binary insertion
		int loser = pairs[i].loser;
		size_t left = 0;
		size_t right = winnerPos;
		while (left < right)
		{
			size_t mid = (left + right) / 2;
			if (sortedWinner[mid] < loser)
				left = mid + 1;
			else
				right = mid;
		}
		sortedWinner.insert(sortedWinner.begin() + left, loser);
		pairs[i].loserInserted = true;
	}
}

static void	insertOtherLosers(std::vector<int>& finalList, std::vector<Pair>& pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (!pairs[i].loserInserted && pairs[i].loser != -1)
		{
			// Insert the loser in the correct position to keep finalList sorted
			int loser = pairs[i].loser;
			size_t winnerPos = pairs[i].winnerInd;
			size_t left = 0;
			size_t right = winnerPos;
			while (left < right)
			{
				size_t mid = (left + right) / 2;
				if (finalList[mid] < loser)
					left = mid + 1;
				else
					right = mid;
			}
			finalList.insert(finalList.begin() + left, loser);
			pairs[i].loserInserted = true;
		}
	}
}

void	PmergeMe::fordJohnFSort(std::vector<int>& v)
{
	std::vector<Pair> pairs;
	size_t i = 0;
	for (; i + 1 < v.size(); i += 2)
	{
		Pair p;
		if (v[i] > v[i + 1])
		{
			p.winner = v[i];
			p.loser = v[i + 1];
			p.winnerInd = i;
			p.loserInserted = false;
		}
		else
		{
			p.winner = v[i + 1];
			p.loser = v[i];
			p.winnerInd = i + 1;
			p.loserInserted = false;
		}
		pairs.push_back(p);
	}
	if (i < v.size()) //for odd
	{
		Pair p;
		p.winner = v[i];
		p.loser = -1;
		p.winnerInd = pairs.size();
		p.loserInserted = false;
		pairs.push_back(p);
	}
	
	//making pairs and sort winner
	std::vector<int> sortedWinner;
	recursiveSort(sortedWinner, pairs);
	
	//putting the right index
	for (size_t idx = 0; idx < sortedWinner.size(); ++idx)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].winner == sortedWinner[idx])
			{
				pairs[j].winnerInd = idx;
				break;
			}
		}
	}
	
	jacobsthalBinary(sortedWinner, pairs);
	insertOtherLosers(sortedWinner, pairs);
	printAfterV(sortedWinner);
}


/*############################################################################################*/
// void	PmergeMe::fordJohnFSort(std::deque<int>& d)
// {
// 	;
// }

//Public Method;
void	PmergeMe::execPmergeMe(int ac, char **av)
{
	this->_rangeSize = ac - 1;
	this->_listV.reserve(_rangeSize);

	//print Before:
	printBefore(av);

	//load:
	loadAllData(av);

	//Algo:
	clock_t start = clock();
	fordJohnFSort(this->_listV);
	clock_t end = clock();
	double duration_vec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

	// clock_t start1 = clock();
	// fordJohnFSort(this->_listDeq);
	// clock_t end1= clock();
	// double duration_deq = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000000.0;

	//print Chrono:
	std::cout << "Time to process a range of " << this->_rangeSize << " elements with std::vector " << duration_vec << " us" << std::endl;
	// std::cout << "Time to process a range of " << this->_rangeSize << " elements with std::deque " << duration_deq << " us" << std::endl;
}