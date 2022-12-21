/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   it_traits.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:18 by plam              #+#    #+#             */
/*   Updated: 2022/12/21 13:01:34 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __IT_TRAITS_HPP__
# define __IT_TRAITS_HPP__

namespace ft {

/* enable_if implementation
** ressource : https://en.cppreference.com/w/cpp/types/enable_if
*/
	template<bool B, class T = void>
	struct enable_if { };

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<class T, T v>
	struct integral_constant {
		static const T					value = v;
		typedef T						value_type;
		typedef integral_constant<T, v>	type;
	};

	struct true_type : ft::integral_constant<bool, true> {};	// true_type : struct that return true for the type T associated
	struct false_type : ft::integral_constant<bool, false> {};	// false_type: struct that return false for the type T associated

	template<typename T>
	struct remove_cv
	{ typedef T type; };

	template<typename T>
	struct remove_cv<const T>
	{ typedef T type; };

	template<typename T>
	struct remove_cv<volatile T>
	{ typedef T type; };

	template<typename T>
	struct remove_cv<const volatile T>
	{ typedef T type; };

	template<typename>
	struct _is_integral_helper : public ft::false_type {};

	template<>
	struct _is_integral_helper<bool> : public ft::true_type {};

	template<>
	struct _is_integral_helper<char> : public ft::true_type {};

	template<>
	struct _is_integral_helper<wchar_t> : public ft::true_type {};

	template<>
	struct _is_integral_helper<signed char> : public ft::true_type {};

	template<>
	struct _is_integral_helper<short int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<long int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<long long int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<unsigned char> : public ft::true_type {};

	template<>
	struct _is_integral_helper<unsigned short int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<unsigned int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<unsigned long int> : public ft::true_type {};

	template<>
	struct _is_integral_helper<unsigned long long int> : public ft::true_type {};

	template<typename T>
	struct is_integral : public ft::_is_integral_helper<typename ft::remove_cv<T>::type>::type {};	
}

#endif