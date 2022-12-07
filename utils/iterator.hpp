/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:44 by plam              #+#    #+#             */
/*   Updated: 2022/12/07 17:29:37 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__


# include <stddef.h>
# include <iterator>
# include "it_traits.hpp"

namespace ft {
	template<typename Category, typename T, typename Distance = ptrdiff_t , typename Pointer = T*, typename Reference = T&>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};
}

#endif