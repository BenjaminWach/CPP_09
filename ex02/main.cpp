/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:05:37 by bwach             #+#    #+#             */
/*   Updated: 2025/05/26 21:33:51 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: missing arguments -> ./a.out ints..." << std::endl;
		return (1);
	}

	PmergeMe sort;
	sort.execPmergeMe(ac, av);

	return (0);
}