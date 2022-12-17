/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:11 by plam              #+#    #+#             */
/*   Updated: 2022/12/17 16:22:59 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TPP__
# define __VECTOR_TPP__

# include <iostream>
# include <stdexcept>
# include <limits>
# include <stddef.h>
# include <functional>
# include <memory>
# include <string>
# include <sstream>
# include "../utils/it_traits.hpp"
# include "../utils/iterator.hpp"
# include "../utils/algo.hpp"

/* Vector container header recreation
** ressource : https://cplusplus.com/reference/vector/vector/
*/

namespace ft {
	template< class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef T											value_type;
			typedef Alloc<value_type>							allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::reference const	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::pointer const		const_pointer;
			typedef typename ft::normal_iterator				iterator;
			typedef typename ft::normal_iterator const			const_iterator;
			typedef typename ft::reverse_iterator				reverse_iterator;
			typedef typename ft::reverse_iterator const			const_reverse_iterator;
	};
}

#endif