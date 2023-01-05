/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackTest.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:43:06 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef stackTEST_HPP
# define stackTEST_HPP

# include "../../includes/All.hpp"

namespace	test_s
{

	void	test_stack(void);
	
	template <class Container, class T>
	void	
	show_stack(const Container &s, std::string name)
	{
		Container	copy;
		
		std::cout << BCyan << "\n\t******** stack " << name << " ******** \n" << Cyan;
		std::cout << "\tsize : " << s.size() << "\n";
		if (!s.size())
		{
			for (size_t i = 0; i < s.size(); ++i)
			{
				std::cout << Yellow "\tstack n^ "  << i << Reset " : " << copy.top() << "\n";
				copy.pop();
			}
		}
	}

	template <class Container, class T>
	void
	print_stack(const Container &s)
	{
		Container	copy(s);
		std::cout << "\n\tstack : [" Purple;
		for (size_t i = 0; i < s.size(); ++i)
		{
			std::cout << copy.top() << (i == s.size() - 1 ? "" : " : ");
			copy.pop();
		}
		std::cout << Reset "]\n";
	}

	template <class Container, class T>
	void	testing_stack(T *init, std::string name)
	{
		Container					s;
	
		show_stack<Container, T>(s, name);
		std::cout << Reset "\tEmpty \t\t : " << (!s.empty() ? Red "false" : Green "true") << "\n";
		std::cout << Reset "\tSize \t\t : " << s.size() << "\n";
		print_stack<Container, T>(s);
		for (int i = 0; i < 9; ++i)
			s.push(init[i]);
		show_stack<Container, T>(s, name);
		std::cout << Reset "\tEmpty \t\t : " << (!s.empty() ? Red "false" : Green "true") << "\n";
		std::cout << Reset "\tSize \t\t : " << s.size() << "\n";
		print_stack<Container, T>(s);
		s.push(init[0]);
		show_stack<Container, T>(s, "");
		std::cout << Reset "\tEmpty \t\t : " << (!s.empty() ? Red "false" : Green "true") << "\n";
		std::cout << Reset "\tSize \t\t : " << s.size() << "\n";
		print_stack<Container, T>(s);
		s.push(init[1]);
		show_stack<Container, T>(s, "");
		std::cout << Reset "\tEmpty \t\t : " << (!s.empty() ? Red "false" : Green "true") << "\n";
		std::cout << Reset "\tSize \t\t : " << s.size() << "\n";
		print_stack<Container, T>(s);
		s.pop();
		show_stack<Container, T>(s, "");
		std::cout << Reset "\tEmpty \t\t : " << (!s.empty() ? Red "false" : Green "true") << "\n";
		std::cout << Reset "\tSize \t\t : " << s.size() << "\n";
		print_stack<Container, T>(s);
		s.pop();
		for (int i = 0; i < 9; ++i)
			s.pop();
		show_stack<Container, T>(s, "");
		std::cout << Reset "\tEmpty \t\t : " << (!s.empty() ? Red "false" : Green "true") << "\n";
		std::cout << Reset "\tSize \t\t : " << s.size() << "\n";
		print_stack<Container, T>(s);
	}

}	// end of namespace


#endif /* ******************************************************* stackTEST_H */