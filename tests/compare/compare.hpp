/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:20:56 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef COMPARE_HPP
# define COMPARE_HPP

# include "../../includes/All.hpp"
# include "../basic/showContainer.hpp"

namespace	test_comp
{
	void	test_compare(void);

	template <class Cont1, class Cont2, class T>
	void
	test_constructor(T *init, size_t size_init, T def, size_t size_def)
	{
		Cont1				my_c1;
		Cont1				my_c2(size_def, def);
		Cont1				my_c3(init, init + size_init);
		Cont1				my_c4(my_c3);

		Cont2				ori_c1;
		Cont2				ori_c2(size_def, def);
		Cont2				ori_c3(init, init + size_init);
		Cont2				ori_c4(ori_c3);

		// show_vector3<my_c1, ori_c1>("My vector", "Original vector");
		// show_vector3(my_c2, ori_c2, "My vector", "Original vector");
		// show_vector3(my_c3, ori_c3, "My vector", "Original vector");
		// show_vector3(my_c4, ori_c4, "My vector", "Original vector");
	}
}

# endif