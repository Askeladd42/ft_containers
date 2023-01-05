/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:20:55 by julpelle          #+#    #+#             */
/*   Updated: 2022/08/04 13:13:29 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "preliminary.hpp"

void	test_pv::test_prelim_v(void)
{
	print_header("vector", "header");
	print_header("Operator Equal", "title");
	test_operator_equal<int>();
	print_header("Begin", "title");
	test_begin<int>();
	print_header("End", "title");
	test_end<int>();
	print_header("Rbegin", "title");
	test_rbegin<int>();
	print_header("Rend", "title");
	test_rend<int>();
	print_header("Size", "title");
	test_size<int>();
	print_header("Max Size", "title");
	test_max_size<int>();
	print_header("Resize", "title");
	test_resize<int>();
	print_header("Capacity", "title");
	test_capacity<int>();
	print_header("Empty", "title");
	test_empty<int>();
	//print_header("Reserve", "title");
	//test_reserve<int>();
	print_header("Operator Access", "title");
	test_operator_access<int>();
	print_header("At", "title");
	test_at<int>();
	print_header("Front", "title");
	test_front<int>();
	print_header("Back", "title");
	test_back<int>();
	print_header("Assign", "title");
	test_assign<int>();
	print_header("Push Back", "title");
	test_push_back<int>();
	print_header("Pop Back", "title");
	test_pop_back<int>();
	//print_header("Insert", "title");
	//test_insert<int>();
	print_header("Erase", "title");
	test_erase<int>();
	print_header("Swap", "title");
	test_swap<int>();
	print_header("Clear", "title");
	test_clear<int>();
}

void	test_ps::test_prelim_s(void)
{
	print_header("stack", "header");
	print_header("Empty", "title");
	test_empty<int>();
	print_header("Size", "title");
	test_size<int>();
	print_header("Top", "title");
	test_top<int>();
	print_header("Push", "title");
	test_push<int>();
	print_header("Pop", "title");
	test_pop<int>();
}

void	test_pm::test_prelim_m(void)
{
	print_header("map", "header");
	print_header("Begin", "title");
	test_begin<char, int>();
	print_header("End", "title");
	test_begin<char, int>();
	print_header("Empty", "title");
	test_empty<char, int>();
	print_header("Size", "title");
	test_size<char, int>();
	print_header("Max size", "title");
	test_max_size<char, int>();
	print_header("Operator Access", "title");
	test_operator_access<char, int>();
	print_header("Insert", "title");
	test_insert<char, int>();
}