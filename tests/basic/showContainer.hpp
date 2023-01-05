/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   showContainer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:23:30 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SHWOCONTAINER_HPP
# define SHWOCONTAINER_HPP

# include "../../includes/All.hpp"

template <class T>
void	
show_vector(const T &cont, std::string name)
{
	typename T::const_iterator	it;
	std::cout << BCyan << "\t******** vector " << name << " ******** \n\t  [ " << Cyan;
	for (typename T::const_iterator jt(cont.begin()); jt != cont.end(); ++jt)
	{
		it = jt;
		std::cout << *jt << (++it != cont.end() ? ", " : "");
	}
	std::cout << BCyan << " ]\n" << Reset;
}

template <class T>
void	
show_vector2(const T &cont, std::string name)
{
	typename T::const_iterator	it;
	std::cout << BCyan << "******** vector " << name << " ******** \n[ " << Cyan;
	for (typename T::const_iterator jt(cont.begin()); jt != cont.end(); ++jt)
	{
		it = jt;
		std::cout << *jt << (++it != cont.end() ? ", " : "");
	}
	std::cout << BCyan << " ]\n" << Reset;
}

template <class Cont1, class Cont2, class T>
void	
show_vector3(std::string name1, std::string name2)
{
	Cont1		cont1;
	Cont2		cont2;
	
	typename T::const_iterator	it;
	std::cout << BCyan << "********  " << name1 << " ******** \t\t " << Cyan;
	std::cout << BCyan << "********  " << name2 << " ******** \n " << Cyan;
	for (typename T::const_iterator jt(cont1.begin()); jt != cont1.end(); ++jt)
	{
		it = jt;
		std::cout << *jt << (++it != cont1.end() ? ", " : "");
	}
	std::cout << "\t\t";
	for (typename T::const_iterator kt(cont2.begin()); kt != cont2.end(); ++kt)
	{
		it = kt;
		std::cout << *kt << (++it != cont2.end() ? ", " : "");
	}
	std::cout << BCyan << " ]\n" << Reset;
}

template <class T>
void	
rshow_vector(const T &cont, std::string name)
{
	typename T::const_reverse_iterator	it;

	std::cout << BCyan << "\t******** vector " << name << " ******** \n\t  [ " << Cyan;
	for (typename T::const_reverse_iterator jt(cont.rbegin()); jt != cont.rend(); ++jt)
	{
		it = jt;
		std::cout << *jt << (++it != cont.rend() ? ", " : "");
	}
	std::cout << Reset << " ] \n";
}

template <class T>
void	
rshow_vector2(const T &cont, std::string name)
{
	typename T::const_reverse_iterator	it;

	std::cout << BCyan << "******** vector " << name << " ******** \n[ " << Cyan;
	for (typename T::const_reverse_iterator jt(cont.rbegin()); jt != cont.rend(); ++jt)
	{
		it = jt;
		std::cout << *jt << (++it != cont.rend() ? ", " : "");
	}
	std::cout << Reset << " ] \n";
}

# endif