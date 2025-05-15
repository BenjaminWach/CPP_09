/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:19:28 by bwach             #+#    #+#             */
/*   Updated: 2025/05/15 04:18:50 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "Error: Invalid number of arguments in command line: ./a.out str" << std::endl;
		return (1);
	}

	Rpn test;
	test.rpnCalculator(av[1]);
	return 0;
}