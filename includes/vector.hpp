/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:11 by plam              #+#    #+#             */
/*   Updated: 2022/12/20 12:29:35 by plam             ###   ########.fr       */
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
	template< class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef T												value_type;
			typedef Allocator<value_type>							allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::normal_iterator<pointer>			iterator;
			typedef typename ft::normal_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	/* default constructor(empty) */
			explicit vector( const allocator_type &alloc = allocator_type() ) :
				this->_alloc(alloc), this->_capacity(0),
				this->_size(0), this->_items(0) {}

	/* fill constructor */
			explicit vector(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()) {
				this->_alloc = alloc;
				this->_capacity = n;
				this->_size = n;
				this->_items = this->_alloc.allocate();

				for (size_type i = 0; i < n; i++)
					this->_alloc[i] = val;
			}
	/* copy constructor */
			vector(const vector	&x) {
				
			}
	/* range consructor */
			template<class InputIterator>
			vector(InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type()) {
				
			}
	/* member functions */
		private:
			Allocator		_alloc;
			size_type		_capacity;
			size_type		_size;
			T				*_items;

	};
}

#endif