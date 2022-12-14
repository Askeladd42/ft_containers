/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:44 by plam              #+#    #+#             */
/*   Updated: 2022/12/14 12:34:32 by plam             ###   ########.fr       */
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
			typedef Iter					iterator_type;
	}
}

#endif