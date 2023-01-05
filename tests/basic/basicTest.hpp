/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicTest.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:18:06 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:03 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BASICTEST_HPP
# define BASICTEST_HPP

# include "../../includes/All.hpp"
# include "showContainer.hpp"

template <class Cont, class T>
void
test_constructor(T *init, size_t size_init, T def, size_t size_def)
{
	Cont				c1;
	Cont				c2(size_def, def);
	Cont				c3(init, init + size_init);
	Cont				c4(c3);

	show_vector(c1, "DEFAULT");
	show_vector(c2, "CONSTRUCT");
	show_vector(c3, "ITERATOR");
	show_vector(c4, "COPY");
}

template <class Cont, class T>
void
test_iterators(T *init, size_t size_init)
{
	Cont				c(init, init + size_init);

	show_vector(c, "");
	rshow_vector(c, "");
}

# endif