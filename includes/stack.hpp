/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:54:29 by plam              #+#    #+#             */
/*   Updated: 2022/12/21 07:51:14 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_TPP__
# define __STACK_TPP

# include "vector.hpp"

class stack : public vector {
	private:
		/* data */
	public:
		stack(/* args */);
		~stack();
};

#endif