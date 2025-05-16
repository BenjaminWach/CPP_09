/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:06:12 by bwach             #+#    #+#             */
/*   Updated: 2025/05/16 18:11:03 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <deque>

class	PmergeMe
{
	private:
			std::vector<int>	_Vec;
			std::deque<int>		_Deq;

			void	fordJohnFSort(std::vector<int>& v);
			void	fordJohnFSort(std::deque<int>& d);

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