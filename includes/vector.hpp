/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:11 by plam              #+#    #+#             */
/*   Updated: 2022/12/16 15:54:15 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_TPP__
# define __VECTOR_TPP__

# include <iostream>
# include <functional>
# include <memory> 

template< typename T >
class vector {
	protected:
		size_t	_size;
	public:
		vector();
		vector(size_t size);
		vector(const vector &other);
		~vector();
};

#endif