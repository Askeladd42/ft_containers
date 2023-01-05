/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:39:40 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:15:34 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/All.hpp"
# include "extras.hpp"
# include "../basic/showContainer.hpp"
# include "../../includes/utils/is_integral.hpp"


void	test_extras::test_extra(void)
{
	print_header("Is Integral", "header");
	test_integral<bool>("bool");
	test_integral<char>("char");
	test_integral<wchar_t>("wchar_t");
	test_integral<signed char>("signed char");
	test_integral<short int>("short int");
	test_integral<int>("int");
	test_integral<long int>("long int");
	test_integral<long long int>("long long int");
	test_integral<unsigned char>("unsigned char");
	test_integral<unsigned short int>("unsigned short int");
	test_integral<unsigned int>("unsigned int");
	test_integral<unsigned long int>("unsigned long int");
	test_integral<unsigned long long int>("unsigned long long int");
	test_integral<float>("float");

	print_header("Equal", "header");
	test_equal<int>();
}