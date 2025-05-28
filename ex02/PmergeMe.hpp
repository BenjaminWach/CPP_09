/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:06:12 by bwach             #+#    #+#             */
/*   Updated: 2025/05/29 00:45:52 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>
#include <vector>
#include <deque>

class	Pair
{
	public:
			Pair();
			Pair(const Pair& rhn);
			Pair& operator=(const Pair& other);
			~Pair();

			int	winner;
			int	loser;
			int	winnerInd;
			bool	winnerPlaced;
			bool	loserInserted;
};

class	PmergeMe
{
	private:
			size_t	_rangeSize;
			std::vector<int>	_listV;
			std::deque<int>		_listDeq;

			void	fordJohnFSort(std::vector<int>& v);
			void	fordJohnFSort(std::deque<int>& d);

			void	loadAllData(char **av);
			void	printBefore(char **av);
			void	printAfterV(const std::vector<int>& sorted);
			void	printAfterD(const std::deque<int>& sorted);

	public:
			PmergeMe();
			PmergeMe(const PmergeMe& rhn);
			~PmergeMe();

			PmergeMe& operator=(const PmergeMe& other);

			void	execPmergeMe(int ac, char **av);
};