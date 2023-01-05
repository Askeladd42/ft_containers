/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:50:54 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 20:00:58 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/All.hpp"
# include "tests/preliminary/preliminary.hpp"
# include "tests/vector/vectorTest.hpp"
# include "tests/stack/stackTest.hpp"
# include "tests/map/mapTest.hpp"
# include "tests/extras/extras.hpp"
# include "includes/utils/is_integral.hpp"

# include <vector>
# include <map>
# include <stack>
# include <algorithm>
# include <type_traits>

void 	print_header(std::string msg, std::string arg)
{
	if (!arg.compare("title"))
		std::cout << BPurple << "\n ====== " << msg << " ====== " << Reset "\n";
	else if (!arg.compare("subtitle"))
		std::cout << BYellow << "\n ------- " << msg << " ------- " << Reset "\n";
	else if (!arg.compare("cat"))
		std::cout << BGreen "\n\t" << msg << Reset " : \n";
	else if (!arg.compare("text"))
		std::cout << Cyan << "\n ** " << msg << " ** " << Reset "\n";
	else if (!arg.compare("header"))
	{
		std::cout << BGreen << "\n=================================== " << Reset "\n";
		std::cout << BGreen << "==========    " << msg << "     ========== " << Reset "\n";
		std::cout << BGreen << "=================================== " << Reset "\n";
	}
}

int 	error_msg(std::string msg, int color, int ret)
{
	std::cout << "Error : ";
	if (color == 1)
		std::cout << Blue << msg << Reset ".\n";
	if (color == 2)
		std::cout << Red << msg << Reset ".\n";
	if (color == 3)
		std::cout << Yellow << msg << Reset ".\n";
	if (color == 4)
		std::cout << Green << msg << Reset ".\n";
	return (ret);
}

void	test_all(void)
{
	test_v::test_vector();
	test_s::test_stack();
	test_extras::test_extra();
	test_m::test_map();
}

int 	main(int ac, char **av)
{
	std::string 	input;

	if (ac > 2)
		return (error_msg("either no arguments (test all) or 1 argument <container type>", 2, 1));
	if (ac == 1)
		test_all();
	else
	{
		input = *(++av);
		if (!input.compare("Vector") || !input.compare("vector"))
			test_v::test_vector();
		else if (!input.compare("Stack") || !input.compare("stack"))
			test_s::test_stack();
		else if (!input.compare("Map") || !input.compare("map"))
			test_m::test_map();
		else if (!input.compare("Extras") || !input.compare("extras"))
			test_extras::test_extra();
		else
			return (error_msg("Type not defined", 2, 1));
	}
	std::cout << std::endl;
	return (0);
}
