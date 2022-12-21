/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:51:17 by plam              #+#    #+#             */
/*   Updated: 2022/12/21 15:10:45 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_HPP__
# define __PAIR_HPP__

#include "iterator.hpp"

namespace ft {
/* Pair of values :
** 
** This class couples together a pair of values, which may be of different types (T1 and T2).
** The individual values can be accessed through its public members first and second.
** 
** Pairs are a particular case of tuple.
*/
	template<class T1, class T2>
	struct pair {
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

	/* (1) default constructor
	** Constructs a pair object with its elements value-initialized.
	*/
		pair() : first(), second() { }

	/*(2) copy / move constructor (and implicit conversion) :
	** The object is initialized with the contents of the pr pair object.
	** The corresponding member of pr is passed to the constructor of each of its members.
	*/
		template<class U, class V>
		pair(const pair<U, V> &pr) : first( pr.first ), second( pr.second ) { }

	/* (3) initialization constructor :
	** Member first is constructed with a and member second with b.
	*/
		pair(const first_type &a, const second_type &b) : first( a ), second( b ) { }
		
	/* Destructor function */
		~pair() { }

	/* Assign contents :
	** Assigns pr as the new content for the pair object.
	** 
	** Member first is assigned pr.first, and member second is assigned pr.second.
	** 
	** The copying forms (1) perform copy assignments, with the elements of its argument 
	** preserving their values after the call. While the moving forms (2) perform move 
	** assignments (as if calling forward for each element), which, for elements of types
	** supporting move semantics implies that these elements of pr are left in an unspecified but valid state.
	*/
		pair	&operator=(const pair &pr) {
			if (&pr == this)
				return *this;
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y){
		return x.first == y.first && x.second == y.second;
	}
	
	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y){
		return !( x == y );
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y){
		return x.first < y.first || (!( y.first < x.first) && x.second < y.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y){
		return !( y < x );
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y){
		return y < x;
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y){
		return !( x < y );
	}


	/* Construct pair object :
	** Constructs a pair object with its first element set to x and its second element set to y.
	** The template types can be implicitly deduced from the arguments passed to make_pair.
	** Pair objects can be constructed from other pair objects containing different types, 
	** if the respective types are implicitly convertible.
	*/
	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y){
		return pair<T1, T2>(x, y);
	}
}

#endif