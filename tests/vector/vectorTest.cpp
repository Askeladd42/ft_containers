/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:33:27 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/14 14:03:35 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vectorTest.hpp"

void	test_v::test_vector(void)
{
	int					int_init[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//double				double_init[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
	//									 0.8, 0.9 };
	std::string			string_init[] = { "A", "B", "C", "D", "E", "F", "G",
										  "H", "I" };

	print_header("vector", "header");		  
	print_header("CONSTRUCTORS", "title");
	print_header("Int", "cat");
	test_constructor<NAMESPACE::vector<int>, int>(int_init, 9, 0, 9);
	print_header("String", "cat");
	test_constructor<NAMESPACE::vector<std::string>, std::string>(string_init, 9, "*", 9);
	
	print_header("CAPACITY", "title");
	print_header("Int values", "subtitle");
	test_capacity<NAMESPACE::vector<int>, int>(0, 9);
	print_header("String values", "subtitle");
	test_capacity<NAMESPACE::vector<std::string>, std::string>("?", 9);
	print_header("Testing iterators values", "subtitle");
	test_iterators<NAMESPACE::vector<int>, int>(int_init, 9);

	print_header("ACCESS", "title");
	print_header("Int values", "subtitle");
	test_access<NAMESPACE::vector<int>, int>(int_init, 9);
	print_header("String values", "subtitle");
	test_access<NAMESPACE::vector<std::string>, std::string>(string_init, 9);

	print_header("MODIFIERS", "title");
	print_header("Int values", "subtitle");
	test_modifiers<NAMESPACE::vector<int>, int>(int_init, 9, 0, 2, 9);
	print_header("String values", "subtitle");
	test_modifiers<NAMESPACE::vector<std::string>, std::string>(string_init, 9, "*", "#", 9);

	print_header("RELATIONNAL OPERATORS", "title");
	print_header("Int values", "subtitle");
	test_operators<NAMESPACE::vector<int>, int>(int_init, 9, 0, 9);
	print_header("String values", "subtitle");
	test_operators<NAMESPACE::vector<std::string>, std::string>(string_init, 9, "*", 9);

}