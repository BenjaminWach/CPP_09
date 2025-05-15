/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:19:47 by bwach             #+#    #+#             */
/*   Updated: 2025/05/15 04:21:00 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>


//stack two operand then apply the operator, than put the res etc
class Rpn
{
	private:
			std::stack<int> _Stack;
			std::string _Input;

			bool	tokenIsOperator(const std::string& token);
			bool	isNumber(const std::string& str);

	public:
			Rpn();
			Rpn(const std::string& input);
			Rpn(const Rpn& rhn);
			~Rpn();

			Rpn& operator=(const Rpn& copy);

			void	rpnCalculator(const std::string& input);
};