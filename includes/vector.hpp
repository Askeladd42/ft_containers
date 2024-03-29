/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:11 by plam              #+#    #+#             */
/*   Updated: 2023/01/10 14:30:37 by plam             ###   ########.fr       */
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
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::normal_iterator<pointer>			iterator;
			typedef typename ft::normal_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			const static size_type	DEF_FACTOR = 2;		// default factor added, can change later on
			Allocator				_alloc;
			size_type				_capacity;
			size_type				_size;
			T						*_items;

			void			OutOfRange(size_type n) const {
				std::stringstream	s;

				s << "n (which is " << n << ") >= this->size() (which is " << this->_size << ")";
				throw std::out_of_range(s.str());
			}

			size_type		get_alloc_size(size_type n) {
				if ((this->_size + n) <= this->_capacity)
					return this->_capacity;
				else if ((this->_capacity + n) > (this->_capacity * DEF_FACTOR))
					return this->_capacity + n;
				else
					return this->_capacity * DEF_FACTOR;
			}

		public:
	/* default constructor(empty) */
			explicit vector(const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _capacity(0),
				_size(0), _items(0) { }

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
			vector(const vector	&x) : _alloc(x._alloc), _capacity(x._capacity),
					_size(x._size), _items(NULL) {
				if (this->_capacity != 0) {
					this->_items = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++) {
						this->_alloc.construct(&this->_items[i], x._items[i]);
					}
				}
			}

	/* range constructor */
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) :	// use the enable_if for the integer case
				_alloc(alloc), _items(NULL) {
				difference_type	size = ft::distance(first, last);

				if (size != 0) {
					this->_items = this->_alloc.allocate(size);

				for (size_type i = 0 ; first != last ; first++, i++) {
					this->_alloc.construct(&this->_items[i], *first);
					}
				}
				this->_size = size;
				this->_capacity = size;
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
			allocator_type	get_allocator() const {
				return this->_alloc;
			}

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
			const_reference	operator[](size_type n) const {
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
					OutOfRange(n);		// to change later
				return this->_items[n];
			}
			const_reference	at(size_type n) const {
				if (n >= this->_size)
					OutOfRange(n);		// to change later
				return this->_items[n];
			}
		/* capacity member function */

		/* Reserve function : Request a change in capacity
		** Requests that the vector capacity be at least enough to contain n elements.
		** If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
		** In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
		** This function has no effect on the vector size and cannot alter its elements.
		*/
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
		/* Resize function : Change size
		** Resizes the container so that it contains n elements.
		**
		** If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
		**
		** If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
		**
		** If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
		**
		** Notice that this function changes the actual content of the container by inserting or erasing elements from it.
		*/
			void			resize(size_type n, value_type val = value_type()) {
				if (n >= this->_size) {
					if (n > this->_capacity)
						reserve(n);
					for (size_type i = this->_size; i < n; i++) {
						this->_alloc.construct(&this->_items[i], val);
					}
					this->_size = n;
				}
				else {
					for (size_type i = n; i < this->_size; i++) {
						this->_alloc.destroy(&this->_items[i]);
					}
				}
			}

			void			shrink_to_fit() {
				if (this->_capacity > this->_size)
					this->_capacity = this->_size;
			}
		/* modifiers member functions */
			/* clear vector function:
			** wipe out all data in the vector
			*/
			void			clear() {
				for (size_type i = 0; i < this->_size; i++) {
					this->_alloc.destroy(&this->_items[i]);
				}
			}
			/* erase function : 
			** position version : 
			** remove the element in position place from the vector, and reducing its size by 1
			** doesn't change the other values of the vector except the one on the previous position
			*/
			iterator		erase(iterator position) {
				difference_type	distance = ft::distance(this->begin(), position);

				if (this->size != 0) {
					size_type	i = distance;
					for (; i < this->_size - 1; i++) {
						this->_items[i] = this->_items[i + 1];
					}
					this->_alloc.destroy(&this->_items[i]);
					this->_size--;
				}
				return iterator(&this->_items[distance]);
			}
			/* erase function : range version : 
			** remove the elements between first and last positions from the vector,
			** and reducing its size by the length from first to last (ie last - first)
			** doesn't change the other values of the vector except the previous erased ones
			*/
			iterator		erase(iterator first, iterator last) {	// need modifications, has many issues
				size_type	len = ft::distance(first, last);
				size_type	i = 0;

				for (; len > 0; i++) {
					this->_alloc.destroy(this->_items[first + i]);
					this->_items[first + i] = this->_items[last + i];
					len--;
				}
				while (i < this->_size) {
					this->_alloc.destroy(&this->_items[first + i]);
					i++;
				}
				return iterator(&this->_items[first]);
			}
			/* insert function :
			** insert the value val before the position given, becoming the new value at this position
			** increasing the size of it ( by one or n elements depending of the method (single or filling))
			**
			** In the case of the range version, it will insert before the position specified 
			** a number of elements equals to the distance betwwen the first last iterator given.
			*/
			iterator		insert(iterator position, const value_type &val) {
				size_type	pos_i = position - this->begin();

				if (this->_size == this->_capacity) {
					size_type	capacity = this->_capacity;

					if (capacity == 0)
						capacity = 1;
					else
						capacity *= DEF_FACTOR;
					reserve(capacity);
				}
				for (size_type i = this->_size; i != pos_i; i--) {
					this->_items[i] = this->_items[i - 1];
				}
				this->_alloc.construct(&this->_items[pos_i], val);
				this->_size++;
				return iterator(&this->_items[pos_i]);
			}
			void			insert(iterator position, size_type n, const value_type &val) {
				iterator		it = position;
				difference_type	distance = ft::distance(this->begin(), position);
				size_type		alloc_size = get_alloc_size(n);

				reserve(alloc_size);
				it = this->begin() + distance;
				for (; n != 0; n--) {
					it = this->insert(it, val);
				}
			}

			template<class InputIterator>
			void			insert(iterator position, InputIterator first, InputIterator last,
								typename ft::enable_if<!ft::is_integral<InputIterator>::value,
								InputIterator>::type* = NULL) {
				difference_type	distance = ft::distance(this->begin(), position);
				difference_type	n = ft::distance(first, last);
				iterator		it;
				size_type		alloc_size = get_alloc_size(n);

				reserve(alloc_size);
				it = this->begin() + distance;
				for (; first != last; first++, it++) {
					it = this->insert(it, *first);
				}
			}

			/* push_back function :
			** Adds a new element at the end of the vector,
			** after its current last element.
			**
			** The content of val is copied (or moved) to the new element.
			**
			** This effectively increases the container size by one,
			** which causes an automatic reallocation of the allocated storage space
			** if -and only if- the new vector size surpasses the current vector capacity.
			*/
			void			push_back(const value_type &val) {
				if (this->_size == this->_capacity) {
					size_type	alloc_size;

					if (this->_size == 0)
						alloc_size = 1;
					else
						alloc_size = this->_capacity * DEF_FACTOR;	// use of the default size allocator
					value_type	*tmp = this->_alloc.allocate(alloc_size);
					for (size_type i = 0; i < this->_size; i++) {
						this->_alloc.construct(&tmp[i], this->_items[i]);
					}
					this->_alloc.deallocate(this->_items, this->_capacity);
					this->_items = tmp;
					this->_capacity = alloc_size;
				}
				this->_items[this->_size++] = val;
			}

			/* pop_back function :
			** Removes the last element in the vector, effectively reducing the container size by one.
			*/
			void			pop_back() {
				if (this->_size != 0) {
					--this->_size;
					this->_alloc.destroy(&this->_items[this->_size - 1]);
				}
			}

			/* assign function :
			** assign/replace the content of the vector by new ones, changing its size if necessary
			*/

			/* In the fill version, the new contents are n elements, each initialized to a copy of val.*/
			void			assign(size_type n, const value_type &val) {
				clear();
				resize(n, val);
			}

			/* In the range version, the new contents are elements  constructed from each of the elements
			** in the range between first and last, in the same order.
			*/
			template< class InputIterator >
			void			assign(InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type* = NULL) {
				clear();
				for (InputIterator it = first ; it != last ; it++) {
					push_back(*it);
				}
			}

			/* swap function :
			** Exchanges the content of the container by the content of x, 
			** which is another vector object of the same type. Sizes may differ.
			**
			** After the call to this member function, the elements in this container are those which were in x before the call,
			** and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
			**
			** Notice that a non-member function exists with the same name, swap,
			** overloading that algorithm with an optimization that behaves like this member function.
			*/
			void			swap(vector& x) {
				Allocator	&tmp_alloc = x._alloc;
				size_type	tmp_size = x._size;
				size_type	tmp_capacity = x._capacity;
				value_type	*tmp_items = x._items;

				x._alloc = this->_alloc;
				x._size = this->_size;
				x._capacity = this->_capacity;
				x._items = this->_items;

				this->_alloc = tmp_alloc;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_items = tmp_items;
			}
			/* iterator usage member functions */
			iterator		begin() {
				return iterator(this->_items);
			}

			const_iterator	begin() const {
				return const_iterator(this->_items);
			}

			reverse_iterator	rbegin() {
				if (this->_items == NULL)
					return reverse_iterator();
				return reverse_iterator(end());
			}

			const_reverse_iterator	rbegin() const {
				if (this->_items == NULL)
					return const_reverse_iterator();
				return const_reverse_iterator(end());
			}

			iterator		end() {
				if (this->_items == NULL)
					return begin();
				return iterator(&this->_items[this->_size]);
			}

			const_iterator	end() const {
				if (this->_items == NULL)
					return begin();
				return const_iterator(&this->_items[this->_size]);
			}

			reverse_iterator		rend() {
				if (this->_items == NULL)
					return rbegin();
				return reverse_iterator(begin());
			}

			const_reverse_iterator	rend() const {
				if (this->_items == NULL)
					return rbegin();
				return const_reverse_iterator(begin());
			}
		};

		template<class T, class Alloc>
		void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y){
			x.swap(y);
		}

		/* comparison functions */
		template<class T, class Alloc>
		bool	operator==(const vector<T, Alloc> &x, const vector<T, Alloc> &y){
			return x.size() == y.size() && ft::equal(x.begin(), x.end(),y.begin(), y.end());
		}
	
		template<class T, class Alloc>
		bool	operator!=(const vector<T, Alloc> &x, const vector<T, Alloc> &y){
			return !(x == y);
		}
	
		template<class T, class Alloc>
		bool	operator<(const vector<T, Alloc> &x, const vector<T, Alloc> &y){
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}
	
		template<class T, class Alloc>
		bool	operator<=(const vector<T, Alloc> &x, const vector<T, Alloc> &y){
			return !(y < x);
		}
	
		template<class T, class Alloc>
		bool	operator>(const vector<T, Alloc> &x, const vector<T, Alloc> &y){
			return (y < x);
		}
	
		template<class T, class Alloc>
		bool	operator>=(const vector<T, Alloc> &x, const vector<T, Alloc> &y){
			return !(x < y);
		}
}

#endif