/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:43:03 by julpelle          #+#    #+#             */
/*   Updated: 2022/07/12 17:06:56 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stackTest.hpp"

void	test_s::test_stack(void)
{
	int					int_init[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::string			string_init[] = { "A", "B", "C", "D", "E", "F", "G",
										  "H", "I" };
	
	print_header(" stack", "header");		  
	print_header("CAPACITY", "title");
	print_header("Int values", "subtitle");
	testing_stack<NAMESPACE::stack<int>, int>(int_init, "");
}

/* ************************************************************************** */