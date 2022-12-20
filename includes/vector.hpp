/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:11 by plam              #+#    #+#             */
/*   Updated: 2022/12/20 15:27:47 by plam             ###   ########.fr       */
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
			vector(const vector	&x) : _alloc(x._alloc()), _capacity(x._capacity()),
					_capacity(x._capacity()), _items (NULL) {
				if (_capacity != 0) {
					this->_items = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++) {
						this->_alloc.construct(&this->_items[i], x._items[i]);
					}
				}
			}

			vector	&operator=(const vector &x) {
				if (*this != x) {

				}
				return *this;
			}

	/* range constructor */
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL ) :
				m_alloc( alloc ), m_items( NULL ) {
					difference_type size = ft::distance(first, last);

					if ( size != 0 ) {
						m_items = m_alloc.allocate( size );

						for ( size_type index = 0 ; first != last ; first++, index++ ){
							m_alloc.construct( &m_items[index], *first );
					}
				}
				m_size = size;
				m_capacity = size;
			}
	/* destructor */
	~vector() {
		if (this->_items != NULL) {
			for (size_type i = 0; i < this->_size; i++) {
				this->_alloc.destroy(&this->_items[i]);
			}
			this->_alloc.deallocate(this->_items, this->_capacity);
		}
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