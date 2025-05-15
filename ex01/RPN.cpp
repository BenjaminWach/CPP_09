/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwach <bwach@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:20:53 by bwach             #+#    #+#             */
/*   Updated: 2025/05/15 04:19:19 by bwach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

//Constructor && destructor:
Rpn::Rpn(): _Input("") {}
Rpn::Rpn(const std::string& input): _Input(input) {}
Rpn::Rpn(const Rpn& rhn)
{
	*this = rhn;
}

Rpn& Rpn::operator=(const Rpn& copy)
{
	if (this != &copy)
	{
		this->_Input = copy._Input;
	}
	return *this;
}

Rpn::~Rpn() {}


//Private Methods:
bool	Rpn::tokenIsOperator(const std::string& token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool	Rpn::isNumber(const std::string& str)
{
	std::istringstream iss(str);
	int n;

	return (iss >> n) && iss.eof();
}


//Public Method:
void	Rpn::rpnCalculator(const std::string& input)
{
	std::istringstream iss(input);
	std::string token;

	while (iss >> token)
	{
		if (isNumber(token))
		{
			std::stringstream ss(token);
			int top;
			ss >> top;
			if (top < 10)
				_Stack.push(top);
			else
				std::cerr << "Error: this exercice doesn't operate decimal number." << std::endl;
		}

		if (tokenIsOperator(token))
		{
			if (_Stack.size() < 2)
			{
				std::cerr << "Error: not enough operand to calculate a result." << std::endl;
				return;
			}

			int b = _Stack.top(); _Stack.pop();
			int a = _Stack.top(); _Stack.pop();

			switch(token[0])
			{
				case '+': 
						_Stack.push(a + b);
						break;
				case '-':
						_Stack.push(a - b);
						break;
				case '*':
						_Stack.push(a * b);
						break;
				case '/':
						if (b == 0)
						{
							std::cerr << "Error: division by zero." << std::endl;
							return;
						}
						_Stack.push(a / b);
						break;
				default:
						std::cerr << "Error: invalid token." << std::endl;
						break;
			}
		}

		if (!isNumber(token) && !tokenIsOperator(token))
		{
			std::cerr << "Error" << std::endl;
			return;
		}
	}
	
	if (_Stack.size() == 1)
		std::cout << _Stack.top() << std::endl;
	else
		std::cerr << "Error" << std::endl;
}