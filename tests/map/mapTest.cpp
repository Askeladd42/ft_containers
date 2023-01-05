/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:13 by julpelle          #+#    #+#             */
/*   Updated: 2022/07/17 16:43:10 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mapTest.hpp"
# include <map>

void	test_m::test_map(void)
{
	NAMESPACE::pair<std::string, int>		si_init[] = {
		NAMESPACE::make_pair("Belier", 1),
		NAMESPACE::make_pair("Taureau", 2),
		NAMESPACE::make_pair("Gémeaux", 3),
		NAMESPACE::make_pair("Cancer", 4),
		NAMESPACE::make_pair("Lion", 5),
		NAMESPACE::make_pair("Vierge", 6),
		NAMESPACE::make_pair("Balance", 7),
		NAMESPACE::make_pair("Scorpion", 8),
		NAMESPACE::make_pair("Sagitaire", 9),
		NAMESPACE::make_pair("Capricorne", 10),
		NAMESPACE::make_pair("Verseau", 11),
		NAMESPACE::make_pair("Poissons", 12),
	};
	NAMESPACE::pair<int, std::string>		is_init[] = {
		NAMESPACE::make_pair(1, "Belier"),
		NAMESPACE::make_pair(2, "Taureau"),
		NAMESPACE::make_pair(3, "Gémeaux"),
		NAMESPACE::make_pair(4, "Cancer"),
		NAMESPACE::make_pair(5, "Lion"),
		NAMESPACE::make_pair(6, "Vierge"),
		NAMESPACE::make_pair(7, "Balance"),
		NAMESPACE::make_pair(8, "Scorpion"),
		NAMESPACE::make_pair(9, "Sagitaire"),
		NAMESPACE::make_pair(10, "Capricorne"),
		NAMESPACE::make_pair(11, "Verseau"),
		NAMESPACE::make_pair(12, "Poissons"),
	};

	NAMESPACE::pair<int, std::string>		test_double[] = {
		NAMESPACE::make_pair(1, "Belier"),
		NAMESPACE::make_pair(2, "Taureau"),
		NAMESPACE::make_pair(4, "Cancer"),
		NAMESPACE::make_pair(5, "Lion"),
		NAMESPACE::make_pair(6, "Vierge"),
		NAMESPACE::make_pair(2, "Taureau"),
		NAMESPACE::make_pair(2, "Taureau"),
		NAMESPACE::make_pair(7, "Balance"),
		NAMESPACE::make_pair(8, "Scorpion"),
		NAMESPACE::make_pair(9, "Sagitaire"),
		NAMESPACE::make_pair(10, "Capricorne"),
		NAMESPACE::make_pair(1, "Belier"),
		NAMESPACE::make_pair(11, "Verseau"),
		NAMESPACE::make_pair(12, "Poissons"),
	};

	NAMESPACE::pair<int, std::string>		test_long[] = {
		NAMESPACE::make_pair(1, "one"),
		NAMESPACE::make_pair(2, "two"),
		NAMESPACE::make_pair(3, "three"),
		NAMESPACE::make_pair(10, "ten"),
		NAMESPACE::make_pair(4, "four"),
		NAMESPACE::make_pair(5, "five"),
		NAMESPACE::make_pair(24, "twenty-four"),
		NAMESPACE::make_pair(6, "six"),
		NAMESPACE::make_pair(7, "seven"),
		NAMESPACE::make_pair(8, "eight"),
		NAMESPACE::make_pair(9, "nine"),
		NAMESPACE::make_pair(13, "thirteen"),
		NAMESPACE::make_pair(23, "twenty-three"),
		NAMESPACE::make_pair(11, "eleven"),
		NAMESPACE::make_pair(12, "twelve"),
		NAMESPACE::make_pair(15, "fifteen"),
		NAMESPACE::make_pair(16, "sixteen"),
		NAMESPACE::make_pair(17, "seventeen"),
		NAMESPACE::make_pair(18, "eightteen"),
		NAMESPACE::make_pair(14, "fourteen"),
		NAMESPACE::make_pair(19, "nineteen"),
		NAMESPACE::make_pair(20, "twenty"),
		NAMESPACE::make_pair(22, "twenty-two"),
		NAMESPACE::make_pair(25, "twenty-five"),
		NAMESPACE::make_pair(26, "twenty-six"),
		NAMESPACE::make_pair(27, "twenty-seven"),
		NAMESPACE::make_pair(28, "twenty-eight"),
		NAMESPACE::make_pair(21, "twenty-one"),
		NAMESPACE::make_pair(29, "twenty-nine"),
		NAMESPACE::make_pair(30, "thirty"),
	};



	print_header(" map", "header");		  
	print_header("CONSTRUCTORS", "title");
	print_header("Int values", "subtitle");
	test_capacity<NAMESPACE::map<int, std::string> >(is_init, 12);
	print_header("String values", "subtitle");
	test_capacity<NAMESPACE::map<std::string, int> >(si_init, 12);
	
	print_header("ACCESS", "title");
	print_header("Int values", "subtitle");
	test_access<NAMESPACE::map<int, std::string> >(is_init, 12);
	print_header("String values", "subtitle");
	test_access<NAMESPACE::map<std::string, int> >(si_init, 12);

	print_header("MODIFIERS", "title");
	print_header("Int values", "subtitle");
	test_modifiers<NAMESPACE::map<int, std::string> >(is_init, 12);
	print_header("String values", "subtitle");
	test_modifiers<NAMESPACE::map<std::string, int> >(si_init, 12);

	print_header("OBSERVERS", "title");
	print_header("Key Compare", "subtitle");
	test_observers<NAMESPACE::map<int, std::string> >(is_init, 12);
	print_header("Value Compare", "subtitle");
	test_observers<NAMESPACE::map<std::string, int> >(si_init, 12);

	print_header("OPERATIONS", "title");
	print_header("Int Values", "subtitle");
	test_operations<NAMESPACE::map<int, std::string> >(is_init, 12);
	print_header("String Values", "subtitle");
	test_operations<NAMESPACE::map<std::string, int> >(si_init, 12);
	print_header("Double Values", "subtitle");
	test_operations<NAMESPACE::map<int, std::string> >(test_double, 14);

	print_header("BIG TEST", "title");
	print_header("Int Values", "subtitle");
	test_operations<NAMESPACE::map<int, std::string> >(test_long, 30);
}