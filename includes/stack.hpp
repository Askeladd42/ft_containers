/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:54:29 by plam              #+#    #+#             */
/*   Updated: 2022/12/21 18:44:13 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_TPP__
# define __STACK_TPP__

# include "vector.hpp"

namespace ft {
template< class T1, class T2 >
class stack : public vector {
	private:
		/* data */
	public:
		stack(/* args */);
		~stack();
	};
}
#endif