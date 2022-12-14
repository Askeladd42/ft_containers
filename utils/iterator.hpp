/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:44 by plam              #+#    #+#             */
/*   Updated: 2022/12/14 15:13:37 by plam             ###   ########.fr       */
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

		/* Arithmetic operator recreation */
	}
}

#endif