/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:06:12 by bwach             #+#    #+#             */
/*   Updated: 2025/05/18 23:20:56 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>
#include <vector>
#include <deque>

class	PmergeMe
{
	private:
			size_t	_rangeSize;
			std::vector<std::pair<int, int> >	_Vec;
			std::deque<std::pair<int, int> >	_Deq;

			void	fordJohnFSort(std::vector<std::pair<int,int> >& v);
			void	fordJohnFSort(std::deque<std::pair<int,int> >& d);

			void	loadAllData(char **av);
			void	printBefore(char **av);
			void	printAfter();

	public:
			PmergeMe();
			PmergeMe(const PmergeMe& rhn);
			~PmergeMe();

			PmergeMe& operator=(const PmergeMe& other);

			void	execPmergeMe(char **av);
};