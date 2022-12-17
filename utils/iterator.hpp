/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:44 by plam              #+#    #+#             */
/*   Updated: 2022/12/17 14:16:31 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__


# include <stddef.h>
# include <iterator>
# include "it_traits.hpp"

namespace ft {
	/*
	** reference : https://en.cppreference.com/w/cpp/iterator/iterator
	*/
	template<typename Category, typename T, typename Distance = ptrdiff_t , typename Pointer = T*, typename Reference = T&>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

/* iterator_traits from it_traits.hpp
** reproducing the std::iterator_traits in the STL library :
** https://en.cppreference.com/w/cpp/iterator/iterator_traits
*/

	template<typename Iterator>
	struct iterator_traits{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template<typename T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef T									*pointer;
		typedef T									&reference;
	};

	template<typename T>
	struct iterator_traits<const T*> {
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef const T								*pointer;
		typedef const T								&reference;
	};

	/* std::distance implementaion
	** reference : https://en.cppreference.com/w/cpp/iterator/distance
	*/

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type result = 0;
		
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	template<class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
	distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) {
		return last - first;
	}

	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last) {
		return ft::distance(first, last, typename iterator_traits<Iterator>::iterator_category());
	}

	/* Reverse iterator
	** reference : https://en.cppreference.com/w/cpp/iterator/reverse_iterator
	*/

	template<class Iter>
	class reverse_iterator : public ft::iterator<
		typename ft::iterator_traits<Iter>::iterator_category,
		typename ft::iterator_traits<Iter>::value_type,
		typename ft::iterator_traits<Iter>::difference_type,
		typename ft::iterator_traits<Iter>::pointer,
		typename ft::iterator_traits<Iter>::reference>
	{
		private:
			Iter							current;
			typedef iterator_traits<Iter>	_traits_type;

/* to_pointer function, inspired by pointer_to function :
** https://en.cppreference.com/w/cpp/memory/pointer_traits/pointer_to
*/

			template<class T>
			static pointer	to_pointer(T p) {
				return p.operator->();
			}

			template<class T>
			static T*		to_pointer(T* p) {
				return p;
			}

		public:
			typedef Iter									iterator_type;
			typedef typename _traits_type::difference_type	difference_type;
			typedef typename _traits_type::pointer			pointer;
			typedef typename _traits_type::reference		reference;

			reverse_iterator() : current() { }
			explicit reverse_iterator( iterator_type x ) : current( x ) { }

			template<class Iter_>
			reverse_iterator	&operator=(reverse_iterator<Iter_> const &other) {
				current = other.base();
				return *this;
			}

			iterator_type base() const {
				return current;
			}

			reference operator*() const {
				iterator_type	tmp = current;
				return *--tmp;
			}

			pointer operator->() const {
				iterator_type	tmp = current;
				--tmp;
				return to_pointer(tmp);				// test of to_pointer function
			}

		/* Arithmetic operator recreation */

		reverse_iterator &operator++() {
			--current;
			return *this;
		}

		reverse_iterator	operator++(int) {
			iterator_type	tmp = current;

			--tmp;
			return tmp;
		}

		reverse_iterator	&operator--() {
			++current;
			return *this;
		}

		reverse_iterator	operator--(int) {
			iterator_type	tmp = current;

			++tmp;
			return tmp;
		}

		reverse_iterator	operator+(difference_type n) const {
			return reverse_iterator(current - n);
		}

		reverse_iterator	&operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		reverse_iterator	operator-(difference_type n) const {
			return reverse_iterator(current + n);
		}
		reverse_iterator	&operator-=(difference_type n) {
			current += n;
			return *this;
		}

		reverse_iterator	&operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template<class Iter>
	inline bool	operator==(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (x.base() == y.base());
	}

	template<class Iter>
	inline bool	operator!=(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (x.base() != y.base());
	}

	template<class Iter>
	inline bool	operator<(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (x.base() < y.base());
	}
	template<class Iter>
	inline bool	operator<=(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (x.base <= y.base());
	}

	template<class Iter>
	inline bool	operator>(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (x.base() > y.base());
	}

	template<class Iter>
	inline bool	operator<=(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (x.base() <= y.base());
	}

	template<class Iter>
	inline reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const &i) {
		return reverse_iterator(i.base() - n);
	}

	template<class Iter>
	inline typename reverse_iterator<Iter>::difference_type
	operator-(reverse_iterator<Iter> const &x, reverse_iterator<Iter> const &y) {
		return (y.base() - x.base());
	}

/* Overload operator for reverse_iterator and const reverse_iterator comparison cases */

	template<class Iter1, class Iter2>
	inline bool	operator==(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (x.base() == y.base());
	}

	template<class Iter1, class Iter2>
	inline bool	operator!=(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (x.base() != y.base());
	}

	template<class Iter1, class Iter2>
	inline bool	operator<(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (x.base() < y.base());
	}
	template<class Iter1, class Iter2>
	inline bool	operator<=(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (x.base <= y.base());
	}

	template<class Iter1, class Iter2>
	inline bool	operator>(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (x.base() > y.base());
	}

	template<class Iter1, class Iter2>
	inline bool	operator<=(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (x.base() <= y.base());
	}

	template<class Iter1, class Iter2>
	inline typename reverse_iterator<Iter1>::difference_type
	operator-(reverse_iterator<Iter1> const &x, reverse_iterator<Iter2> const &y) {
		return (y.base() - x.base());
	}

/*
** Random access iterator class recreation
*/

	template<class Iterator>
	class normal_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iterator> {
		private:
			typedef iterator_traits<Iter>	_traits_type;
		public:
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename _traits_type::difference_type	difference_type;
			typedef typename _traits_type::pointer			pointer;
			typedef typename _traits_type::reference		reference;

			/* iterator constructors7 destructors */
			normal_iterator() : current( iterator_type() ) { }
			explicit normal_iterator(iterator_type const &p) : current( p ) { }
			~normal_iterator() { }
	}



/* enable_if implementation
** ressource : https://en.cppreference.com/w/cpp/types/enable_if
*/

}

#endif