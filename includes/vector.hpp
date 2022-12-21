/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:11 by plam              #+#    #+#             */
/*   Updated: 2022/12/21 17:30:45 by plam             ###   ########.fr       */
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
		private:
			Allocator		_alloc;
			size_type		_capacity;
			size_type		_size;
			T				*_items;

			allocator_type	get_allocator() const {
				return this->_alloc;
			}
			void			OutOfRange(size_type n) const {
				std::stringstream	s;

				s << "n (which is " << n << ") >= this->size() (which is " << m_size << ")";
				throw std::out_of_range(s.str());
			}

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
					_size(x._size()), _items (NULL) {
				if (this->_capacity != 0) {
					this->_items = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++) {
						this->_alloc.construct(&this->_items[i], x._items[i]);
					}
				}
			}

	/* range constructor */
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL ) :	// use the enable_if for the integer case
				this->_alloc(alloc), this->_items(NULL) {
				difference_type size = ft::distance(first, last);

				if (size != 0) {
					this->_items = this->_alloc.allocate(size);

				for (size_type i = 0 ; first != last ; first++, i++) {
					this->_alloc.construct(&this->_items[index], *first);
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

	/* assign operator */
			vector	&operator=(const vector &x) {
				if (this != &x) {
					this->clear();	//Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
					this->reserve(x->_capacity);	//restore the capacity of the vector
					
					for (size_type i = 0; i < x.size; i++) {
						this->_alloc.construct(&this->_items[i], x._items[i]);
					}
					this->_size = x.size();
				}
				return *this;
			}

	/* member functions */
		/* "getter" functions */
			size_type	size() {				// returns the size (i.e. the number of elements) of the vector
				return this->_size;
			}

			size_type	capacity() {			// returns the capacity (i.e. the number of elements the vector can handle)
				return this->_capacity;			// capacity >= size, can be altered by the memer function vector::reserve
			}
			size_type	max_size() const {		// returns the max size that can be allocated to the vector
				return this->_alloc.max_size();
			}

			bool	empty() const {				// test if the vector is empty (i.e. if the vector has elements in it)
				return (this->_size == 0);
			}

		/* element access member functions */
			reference		operator[](size_type n) {
				return this->_items[n];
			}
			const_reference	operator[](size_type n) {
				return this->_items[n];
			}

			reference		front() {
				return this->_items[0];
			}
			const_reference	front() const {
				return this->_items[0];
			}
			
			reference		back() {
				size_type n = (this->_size == 0) ? 0 : this->_size - 1;
				return this->_items[n];
			}
			const_reference	back() const {
				size_type n = (this->_size == 0) ? 0 : this->_size - 1;
				return this->_items[n];
			}

			reference		at(size_type n) {
				if (n >= this->_size)
					throw OutOfRange(n);		// to change later
				return this->_items[n];
			}
			const_reference	at(size_type n) {
				if (n >= this->_size)
					throw OutOfRange(n);		// to change later
				return this->_items[n];
			}
		/* capacity member function */
			void			reserve(size_type n) {
				if (n > this->max_size()) {
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				}
				if (n > this->_capacity) {
					T	*tmp = this->_alloc.allocate(n);

					if (this->_items != NULL) {
						for (size_type i = 0; i < this->_size; i++) {
							this->_alloc.construct(&tmp[i], this->_items[i]);
						}
						this->_alloc.deallocate(this->_items, this->_capacity);
					}
					this->_items = tmp;
					this->_capacity = n;
				}
			}

			void			resize(size_type n, value_type val = value_type()) {
				if (n > this->_size) {
					if (n > this->_capacity)
					for (size_type i = this->back; i < n; i++) {
						T	*tmp = this->_alloc.allocate(n);
					}
				}
				else {
					for (size_type i = n; i < this->_size; i++) {
						this->_alloc.destroy(&this->_items[i]);
					}
					this->_size = n;
				}
			}

			void			shrink_to_fit() {
				if (this->_capacity > this->_size)
					this->_capacity = this->_size;
			}
		/* modifiers member functions */
			void	clear() {
				for (size_type i = 0; i < this->_size; i++) {
					this->_alloc.destroy(this->_items[i]);
				}
			}

			iterator		erase(normal_iterator pos) {
				this->_alloc.destroy(this->_items[pos]);
			}
			iterator		erase(normal_iterator first, normal_iterator last) {
				for (; first < last; ++first) {
					this->_alloc.destroy(this->_items[first]);
				}
			}

			iterator		insert(iterator position, const value_type &val) {

			}
			void			insert(iterator position, size_type n, const value_type &val);
			template< class InputIterator >
			void			insert(iterator position, InputIterator first, InputIterator last);

			void			assign(size_type n, const value_type &val);
			template< class InputIterator >
			void 			assign(InputIterator first, InputIterator last);

			void			pop_back();
			void			push_back(const value_type &val);
	};
}

#endif