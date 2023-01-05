/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorTest.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:33:28 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:18 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef vectorTEST_HPP
# define vectorTEST_HPP

# include "../../includes/All.hpp"

namespace	test_v
{

	void	test_vector(void);

	template <class Container, class T>
	void
	test_capacity(T init, size_t size_init)
	{
		Container			c;

		std::cout << "\tSize \t\t: " << c.size() << "\n";
		std::cout << "\tMax size \t: " << c.max_size() << "\n";
		std::cout << "\tEmpty \t\t: " << c.empty() << "\n";
		c.resize(size_init, init);
		show_vector(c, "");
		std::cout << "\tCapacity \t: " << c.capacity() << "\n";
		std::cout << "\tEmpty \t\t: " << c.empty() << "\n";
		c.resize(5);
		show_vector(c, "");
		std::cout << "\tReserve of \t: 5\tCapacity \t: " << c.capacity() << "\n";
		c.reserve(11);
		std::cout << "\tReserve of \t: 11\tCapacity \t: " << c.capacity() << "\n";
		c.reserve(17);
		std::cout << "\tReserve of \t: 17\tCapacity \t: " << c.capacity() << "\n";
	}

	template <class Container, class T>
	void
	test_access(T *init, size_t size_init)
	{
		Container			c(init, init + size_init);

		std::cout << "\n";
		show_vector(c, "");
		std::cout << "\n";
		std::cout << "\tShowing 2nd element \t: " << c[1] << " | " << c.at(1) << "\n";
		std::cout << "\tShowing 4th element \t: " << c[3] << " | " << c.at(3) << "\n";
		std::cout << "\tShowing front \t\t: " << c.front() << "\n";
		std::cout << "\tShowing back \t\t: " << c.back() << "\n";
	}

	template <class Container, class T>
	void
	test_modifiers(T *init, size_t size_init, T def, T var, size_t size_def)
	{
		Container			c1;
		Container			c2(init, init + size_init);

		std::cout << Blue "\n\tEmpty container \n" Reset;
		show_vector(c1, "ORIGINAL");
		std::cout << Blue "\n\tCopied container \n" Reset;
		show_vector(c2, "COPY");
		std::cout << "\n";
		std::cout << Yellow"\tafter assigning default value : \n" Reset;
		c1.assign(size_def, def);
		show_vector(c1, "ORIGINAL");
		std::cout << Yellow"\tafter pushing back default value : \n" Reset;
		c1.push_back(def);
		show_vector(c1, "ORIGINAL");
		std::cout << Yellow"\tafter double poping back default value : \n" Reset;
		c1.pop_back();
		c1.pop_back();
		show_vector(c1, "ORIGINAL");
		std::cout << Yellow"\tafter inserting var at position 0, 1 and 3: \n" Reset;
		c1.insert(c1.begin(), (size_t)2, var);
		c1.insert(c1.begin() + 3, (size_t)1, var);
		show_vector(c1, "ORIGINAL");
		std::cout << Yellow"\tafter erase first element: \n" Reset;
		c1.erase(c1.begin());
		show_vector(c1, "ORIGINAL");

		std::cout << Yellow"\tCurrent container \n" Reset;
		show_vector(c1, "ORIGINAL");
		show_vector(c2, "COPY");
		std::cout << Yellow"\tSwapping container \n" Reset;
		c1.swap(c2);
		show_vector(c1, "ORIGINAL");
		show_vector(c2, "COPY");
		std::cout << Yellow"\tClearing containers \n" Reset;
		c1.clear();
		c2.clear();
		show_vector(c1, "ORIGINAL");
		show_vector(c2, "COPY");

		std::cout << "\n";
	}

	template <class Container, class T>
	void
	test_operators(T *init, size_t size_init, T def, size_t size_def)
	{
		Container		c1(size_def, def);
		Container		c2(init, init + size_init);
		Container		c3(c2);
		Container		c4(c2);
		Container		c5(c2);
		Container		c6(c2);


		std::cout << Yellow "\nContainer 1 vs Container 2 : \n";
		show_vector(c1, "Container 1");
		show_vector(c2, "Container 2");
		std::cout << "\n";
		std::cout << Reset "\tContainer 1 == Container 2 ? \t " << (c1 == c2 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 == Container 1 ? \t " << (c1 == c1 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 != Container 2 ? \t " << (c1 != c2 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 != Container 1 ? \t " << (c1 != c1 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 < Container 1 ? \t " << (c1 < c1 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 <= Container 1 ? \t " << (c1 <= c1 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 > Container 1 ? \t " << (c1 > c1 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 1 >= Container 1 ? \t " << (c1 >= c1 ? Green "true\n" : Red "false\n");
		std::cout << "\n";
		c3.push_back(def);
		std::cout << Yellow "\nContainer 3 vs Container 4 : \n";
		show_vector(c3, "Container 3");
		show_vector(c4, "Container 4");
		std::cout << "\n";
		std::cout << Reset "\tContainer 3 < Container 4 ? \t " << (c3 < c4 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 3 > Container 4 ? \t " << (c3 > c4 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 3 <= Container 4 ? \t " << (c3 <= c4 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 3 >= Container 4 ? \t " << (c3 >= c4 ? Green "true\n" : Red "false\n");
		std::cout << Yellow "\nContainer 5 vs Container 6 : \n";
		c5.pop_back();
		show_vector(c5, "Container 5");
		show_vector(c6, "Container 6");
		std::cout << "\n";
		std::cout << Reset "\tContainer 5 == Container 6 ? \t " << (c5 == c6 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 5 != Container 6 ? \t " << (c5 != c6 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 5 < Container 6 ? \t " << (c5 < c6 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 5 > Container 6 ? \t " << (c5 > c6 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 5 <= Container 6 ? \t " << (c5 <= c6 ? Green "true\n" : Red "false\n");
		std::cout << Reset "\tContainer 5 >= Container 6 ? \t " << (c5 >= c6 ? Green "true\n" : Red "false\n");
	}


}	// end of namespace

# endif