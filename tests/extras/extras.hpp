/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:26:45 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXTRAS_HPP
# define EXTRAS_HPP

# include "../../includes/All.hpp"

namespace test_extras
{
	void	test_extra(void);

	template <class T>
	void
	test_integral(const char *str)
	{
		std::cout << str << " : ";
		if (NAMESPACE::is_integral<T>::value == 1)
			std::cout << Green "true" << Reset "\n";
		else
			std::cout << Red "false" << Reset "\n";
	}

	template <class T>
	void
	test_equal(void)
	{
		NAMESPACE::vector<T>	vec1;
		
		for (int i=1; i <= 10; i++)
			vec1.push_back(i);
		
		NAMESPACE::vector<T>	vec2(vec1);

		if (NAMESPACE::equal (vec1.begin(), vec1.end(), vec2.begin()))
			std::cout << Green "Both vectors are equal\n" Reset;
		else
			std::cout << Red "vectors are not equal\n" Reset;
		
		vec1[3] = 12;

		if (NAMESPACE::equal (vec1.begin(), vec1.end(), vec2.begin()))
			std::cout << Green "Both vectors are equal\n" Reset;
		else
			std::cout << Red "vectors are not equal\n" Reset;
	}
}


# endif