/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:54:29 by plam              #+#    #+#             */
/*   Updated: 2023/01/10 14:31:37 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_TPP__
# define __STACK_TPP__

# include "vector.hpp"

namespace ft {
	/* Stack container implementation :
	** ressource : https://www.cplusplus.com/reference/stack/stack
	*/
	template<class T, class Container = ft::vector<T> >
	class stack {
			template<class _T, class _Container>
			friend bool	operator==(const stack<_T, _Container> &, const stack<_T, _Container> &);

			template<class _T, class _Container>
			friend bool	operator<(const stack<_T, _Container> &, const stack<_T, _Container> &);

		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef std::size_t	size_type;
		protected:
			container_type		c;

		public:
			/* stack construct function :
			** Constructs a stack container adaptor object.
			*/
			explicit stack(const container_type &container = container_type()) 
				: c( container ) { }
			
			/* stack copy constructor */
			stack(const stack &s) : c(s.c) {}

			/* stack assignation constructor */
			stack	&operator=(const stack &s) {
				if (&s != this)
					this->c = s.c;
				return *this;
			}

			/* stack default destructor */
			virtual ~stack() { }
			
			/* size getter function :
			** Returns the number of elements in the stack.
			**
			** This member function effectively calls member size of the underlying container object.
			*/
			size_type	size() const {
				return this->c.size();
			}

			/* empty stack function tester:
			** Returns whether the stack is empty: i.e. whether its size is zero.
			**
			** This member function effectively calls member empty of the underlying container object.
			*/
			bool		empty() const {
				return (size() == 0);
			}

			/* Access next element :
			** Returns a reference to the top element in the stack.
			**
			** Since stacks are last-in first-out containers,
			** the top element is the last element inserted into the stack.
			**
			** This member function effectively calls member back of the underlying container object
			*/
			value_type	&top() {
				return this->c.back();
			}

			const value_type &top() const {
				return this->c.back();
			}

			/* Insert element :
			** Inserts a new element at the top of the stack, above its current top element. 
			** The content of this new element is initialized to a copy of val.
			** 
			** This member function effectively calls the member function push_back
			** of the underlying container object.
			*/
			void	push(const value_type &val) {
				this->c.push_back(val);
			}

			/* Remove top element :
			** Removes the element on top of the stack, effectively reducing its size by one.
			**
			** The element removed is the latest element inserted into the stack,
			** whose value can be retrieved by calling member stack::top.
			**
			** This calls the removed element's destructor.
			**
			** This member function effectively calls the member function
			** pop_back of the underlying container object.
			*/
			void	pop() {
				this->c.pop_back();
			}
	};
	/* comparison member functions */
	template<class T, class Container>
	bool operator==(const stack<T, Container> &x, const stack<T, Container> &y) {
		return x.c == y.c;
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &x, const stack<T, Container> &y) {
		return x.c < y.c;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &x, const stack<T, Container> &y){
		return !(x == y);
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &x, const stack<T, Container> &y){
		return (y < x);
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &x, const stack<T, Container> &y){
		return !(x < y);
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &x, const stack<T, Container> &y){
		return !(y < x);
	}
}

#endif