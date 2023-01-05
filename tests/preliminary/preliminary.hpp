/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julpelle <julpelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:12:13 by julpelle          #+#    #+#             */
/*   Updated: 2022/12/29 13:14:39 by julpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PRELIMINARY_HPP
# define PRELIMINARY_HPP

# include "../../includes/All.hpp"
# include "../basic/showContainer.hpp"
# include "../map/mapTest.hpp"

namespace	test_pv
{

	void	test_prelim_v(void);
	
	template <class T>
	void
	test_operator_equal(void)
	{
		NAMESPACE::vector<T>  foo (3);
		NAMESPACE::vector<T>  bar (5);

		bar = foo;
		foo = NAMESPACE::vector<T>();

		std::cout << "Size of foo " << int(foo.size()) << "\n";
		std::cout << "Size of bar " << int(bar.size()) << "\n";
	}

	template <class T>
	void
	test_begin(void)
	{
		NAMESPACE::vector<T>	a;
		for (int i =1; i <= 5; i++)
			a.push_back(i);
		show_vector2(a, "");
		std::cout << '[';
		for (typename NAMESPACE::vector<T>::iterator it = a.begin(); it != a.end(); ++it)
		{
			std::cout << ' ' << *it;
			if (it != a.end() - 1)
				std::cout << ',';
		}
		std::cout << " ]\n";
	}

	template <class T>
	void
	test_end(void)
	{
		NAMESPACE::vector<T>	a;
		for (int i =1; i <= 5; i++)
			a.push_back(i);
		rshow_vector2(a, "");
		std::cout << '[';
		for (typename NAMESPACE::vector<T>::iterator it = a.end() - 1; it != a.begin() - 1; --it)
		{
			std::cout << ' ' << *it;
			if (it != a.begin())
				std::cout << ',';
		}
		std::cout << " ]\n";
	}

	template <class T>
	void
	test_rbegin(void)
	{
		NAMESPACE::vector<T>	a;
		for (int i =1; i <= 5; i++)
			a.push_back(i);
		rshow_vector2(a, "");
		std::cout << '[';
		for (typename NAMESPACE::vector<T>::reverse_iterator it = a.rbegin(); it != a.rend(); ++it)
		{
			std::cout << ' ' << *it;
			if (it != a.rend() - 1)
				std::cout << ',';
		}
		std::cout << " ]\n";
	}

	template <class T>
	void
	test_rend(void)
	{
		NAMESPACE::vector<T>	a;
		for (int i =1; i <= 5; i++)
			a.push_back(i);
		show_vector2(a, "");
		std::cout << '[';
		for (typename NAMESPACE::vector<T>::reverse_iterator it = a.rend() - 1; it != a.rbegin() - 1; --it)
		{
			std::cout << ' ' << *it;
			if (it != a.rbegin())
				std::cout << ',';
		}
		std::cout << " ]\n";
	}

	template <class T>
	void
	test_size(void)
	{
		NAMESPACE::vector<T>	a;
		for (int i = 1; i <= 5; i++)
			a.push_back(i);
		show_vector2(a, "");
		std::cout << "0.size : " << a.size() << "\n";
		for (int i = 6; i <= 10; i++)
			a.push_back(i);
		show_vector2(a, "");
		std::cout << "1.size : " << a.size() << "\n";
		for (int i = 11; i <= 100; i++)
			a.push_back(i);
		show_vector2(a, "");
		std::cout << "1.size : " << a.size() << "\n";
		
	}

	template <class T>
	void
	test_max_size(void)
	{
		NAMESPACE::vector<T> test;
		for (int i = 0; i < 100; i++)
			test.push_back(i);
		std::cout << "Size : " << test.size() << "\n";
		std::cout << "Max size : " << test.max_size() << "\n";
	}

	template <class T>
	void
	test_resize(void)
	{
		NAMESPACE::vector<T> test;
		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Size : " << test.size() << "\n";
		test.resize(20);
		show_vector2(test, "");
		std::cout << "Size : " << test.size() << "\n";
		test.resize(50, 100);
		show_vector2(test, "");
		std::cout << "Size : " << test.size() << "\n";
	}

	template <class T>
	void
	test_capacity(void)
	{
		NAMESPACE::vector<T>	test;
		
		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Capacity : " << test.capacity() << "\n";
		for (int i = 11; i <= 20; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Capacity : " << test.capacity() << "\n";
		for (int i = 21; i <= 50; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Capacity : " << test.capacity() << "\n";
	}

	template <class T>
	void
	test_empty(void)
	{
		NAMESPACE::vector<T>	test;
		NAMESPACE::vector<T>	empty;
		
		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		show_vector2(empty, "");
		std::cout << "1st vector is empty ? : ";
		if (test.empty())
			std::cout << Green "true" << Reset "\n";
		else
			std::cout << Red "false" << Reset "\n";
		std::cout << "2nd vector is empty ? : ";
		if (empty.empty())
			std::cout << Green "true" << Reset "\n";
		else
			std::cout << Red "false" << Reset "\n";
	}

	template <class T>
	void
	test_reserve(void)
	{
		typename NAMESPACE::vector<T>::size_type size;
		NAMESPACE::vector<T>	foo;

		size = foo.capacity();
		std::cout << "Expanding foo " << "\n";
		for (int i=0; i<100; ++i)
		{
			foo.push_back(i);
			if (size != foo.capacity()) 
			{
				size  = foo.capacity();
				std::cout << "capacity changed: " << size  << '\n';
			}
  		}
		  
		NAMESPACE::vector<int> bar;
		size = bar.capacity();
		bar.reserve(100);
		std::cout << "making bar grow:\n";
		for (int i=0; i<100; ++i)
		{
			bar.push_back(i);
			if (size!=bar.capacity())
			{
				size = bar.capacity();
				std::cout << "capacity changed: " << size << '\n';
			}
		}
	}

	template <class T>
	void
	test_operator_access(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Elem 0 : " << test[0] << "\n";
		std::cout << "Elem 1 : " << test[1] << "\n";
		std::cout << "Elem 4 : " << test[4] << "\n";
		std::cout << "Elem 9 : " << test[9] << "\n";
	}

	template <class T>
	void
	test_at(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Elem at pos 0 : " << test.at(0) << "\n";
		std::cout << "Elem at pos 2 : " << test.at(2) << "\n";
		std::cout << "Elem at pos 6 : " << test.at(6) << "\n";
	}

	template <class T>
	void
	test_front(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i =1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Front elem : " << test.front() << "\n";
	}

	template <class T>
	void
	test_back(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i =1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		std::cout << "Back elem : " << test.back() << "\n";
		test.pop_back();
		show_vector2(test, "");
		std::cout << "Back elem : " << test.back() << "\n";
	}

	template <class T>
	void
	test_assign()
	{
		NAMESPACE::vector<T>	first;
		NAMESPACE::vector<T>	second;

		for (int i=1; i <= 10; i++)
			first.push_back(i);
		typename NAMESPACE::vector<T>::iterator f;
		typename NAMESPACE::vector<T>::iterator l;
		f = first.begin() + 1;
		l = first.end() - 1;
		second.assign(f, first.end() - 1);
		show_vector2(first, "first");
		show_vector2(second, "second");
		std::cout << "Size of first : " << first.size() << "\n";
		std::cout << "Size of second : " << second.size() << "\n";
	}

	template <class T>
	void
	test_push_back(void)
	{
		NAMESPACE::vector<T>	test;

		show_vector2(test, "");
		test.push_back(1);
		show_vector2(test, "");
		for (int i = 2; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
	}
	
	template <class T>
	void
	test_pop_back(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		for (int i = 1; i <= 10; i++)
		{
			test.pop_back();
			show_vector2(test, "");
		}
	}

	template <class T>
	void
	test_insert(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		typename NAMESPACE::vector<T>::iterator it;

		it = test.begin();
		test.insert(it + 2, 0);
		test.insert(it + 10, 0);
		show_vector2(test, "");
	}

	template <class T>
	void
	test_erase(void)
	{
		NAMESPACE::vector<T>	test;

		for (int i=1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		test.erase(test.begin() + 4);
		test.erase(test.begin() + 4);
		test.erase(test.begin() + 4);
		show_vector2(test, "");
	}

	template <class T>
	void	
	test_swap(void)
	{
		NAMESPACE::vector<T> test;
		NAMESPACE::vector<T> test2;
		NAMESPACE::vector<T> tmp;

		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		for (int i = 11; i <= 20; i++)
			test2.push_back(i);
		show_vector2(test, "1");
		show_vector2(test2, "2");
		tmp = test;
		test.swap(test2);
		test2.swap(tmp);
		show_vector2(test, "1");
		show_vector2(test2, "2");
	}

	template <class T>
	void
	test_clear(void)
	{
		NAMESPACE::vector<T> test;

		for (int i = 1; i <= 10; i++)
			test.push_back(i);
		show_vector2(test, "");
		test.clear();
		show_vector2(test, "");
	}
}

namespace	test_ps
{
	void	test_prelim_s(void);

	template <class T>
	void
	test_empty(void)
	{
		NAMESPACE::stack<T>	st;

		for (int i = 1; i <= 10; i++)
			st.push(i);
		std::cout << "stack is empty ? : ";
		if (st.empty())
			std::cout << Green "true\n" Reset;
		else
			std::cout << Red "false\n" Reset;
		while (!st.empty())
			st.pop();
		std::cout << "stack is empty ? : ";
		if (st.empty())
			std::cout << Green "true\n" Reset;
		else
			std::cout << Red "false\n" Reset;
	}

	template <class T>
	void
	test_size(void)
	{
		NAMESPACE::stack<T>	st;

		std::cout << "Size : " << st.size() << "\n";
		std::cout << "Now stack contains : [";
		for (int i = 1; i <= 10; i++)
		{
			st.push(i);
			std::cout << " " << i;
			if (i < 10)
				std::cout << " ,";
			else
				std::cout << " ]\n";
		}
		std::cout << "Size : " << st.size() << "\n";
	}
	
	template <class T>
	void
	test_top(void)
	{
		NAMESPACE::stack<T>	st;

		std::cout << "Size : " << st.size() << "\n";
		std::cout << "Now stack contains : [";
		for (int i = 1; i <= 10; i++)
		{
			st.push(i);
			std::cout << " " << i;
			if (i < 10)
				std::cout << " ,";
			else
				std::cout << " ]\n";
		}
		for (int i = 1; i <= 10; i++)
		{
			std::cout << "Top : " << st.top() << " then pop\n";
			st.pop();
		}
	}

	template <class T>
	void
	test_push(void)
	{
		NAMESPACE::stack<T>	st;

		for (int i = 1; i <= 10; i++)
		{
			std::cout << "Pushing : " << i;
			st.push(i);
			std::cout << " and now top is : " << st.top() << "\n";
		}
	}

	template <class T>
	void
	test_pop(void)
	{
		NAMESPACE::stack<T>	st;

		std::cout << "Adding then popping even numbers\n";
		std::cout << "Now stack contains : [";
		for (int i = 1; i <= 10; i++)
		{
			st.push(i);
			if (i % 2 == 0)
				st.pop();
			std::cout << " " << st.top();
			if (i < 10)
				std::cout << " ,";
			else
				std::cout << " ]\n";
		}
		
	}
}

namespace	test_pm
{
	void	test_prelim_m(void);

	template <class Key, class T>
	void
	test_begin(void)
	{
		NAMESPACE::map<Key, T>	map;
		
		map['a'] = 200;
		map['b'] = 100;
		map['c'] = 300;

		for (typename NAMESPACE::map<Key, T>::iterator it = map.begin(); it != map.end(); ++it)
			std::cout << it->first << " => " << it->second << "\n";
	}

	template <class Key, class T>
	void	
	test_end(void)
	{
		NAMESPACE::map<Key, T>	map;

		map['a'] = 200;
		map['b'] = 100;
		map['c'] = 300;

		for (typename NAMESPACE::map<Key, T>::iterator it = map.begin(); it != map.end(); ++it)
			std::cout << it->first << " => " << it->second << "\n";
	}

	template <class Key, class T>
	void
	test_rbegin(void)
	{
		NAMESPACE::map<Key, T>	map;
		
		map['a'] = 100;
		map['b'] = 200;
		map['c'] = 300;

		for (typename NAMESPACE::map<Key, T>::iterator rit = map.rbegin(); rit != map.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << "\n";
	}

	template <class Key, class T>
	void
	test_rend(void)
	{
		NAMESPACE::map<Key, T>	map;
		
		map['a'] = 100;
		map['b'] = 200;
		map['c'] = 300;

		for (typename NAMESPACE::map<Key, T>::reverse_iterator rit = map.rend(); rit != map.rbegin(); --rit)
			std::cout << rit->first << " => " << rit->second << "\n";
	}

	template <class Key, class T>
	void
	test_empty(void)
	{
		NAMESPACE::map<Key, T>	map;

		std::cout << "map is empty ? : ";
		if (!map.empty())
			std::cout << Green "true\n" Reset;
		else
			std::cout << Red "false\n" Reset;
			
		map['a'] = 100;
		map['b'] = 200;
		map['c'] = 300;

		std::cout << "map is empty ? : ";
		if (!map.empty())
			std::cout << Green "true\n" Reset;
		else
			std::cout << Red "false\n" Reset;
	}

	template <class Key, class T>
	void
	test_size(void)
	{
		NAMESPACE::map<Key, T>	map;

		std::cout << "map size is : " << map.size() << "\n";
		map['a'] = 1;
		map['b'] = 2;
		map['c'] = 3;
		std::cout << "map size is : " << map.size() << "\n";
		map['c'] = 4;
		std::cout << "map size is : " << map.size() << "\n";
		map['d'] = 5;
		std::cout << "map size is : " << map.size() << "\n";
	}

	template <class Key, class T>
	void
	test_max_size(void)
	{
		NAMESPACE::map<Key, T>	map;

		std::cout << "Max size : " << map.max_size() << "\n";
	}

	template <class Key, class T>
	void
	test_operator_access(void)
	{
		NAMESPACE::map<Key, T>	map;

		std::cout << "map [0] : " << map[0] << "\n";
		for (char i = 1; i <= 20; i++)
			map[i] = (int)i;
		std::cout << "map [0] : " << map[0] << "\n";
		std::cout << "map [3] : " << map[3] << "\n";
		std::cout << "map [15] : " << map[15] << "\n";
	}

	template <class Key, class T>
	void
	test_insert(void)
	{
		NAMESPACE::map<Key, T>	map;
		
		std::cout << "map size is : " << map.size() << "\n";
		map.insert(NAMESPACE::pair<Key, T>('a', 100));
		map.insert(NAMESPACE::pair<Key, T>('b', 200));
		std::cout << "map size is : " << map.size() << "\n";
		typename NAMESPACE::map<Key, T>::iterator it = map.begin();
		map.insert(it, NAMESPACE::pair<Key, T>('c', 300));
		std::cout << "map size is : " << map.size() << "\n";
	}
	
}

# endif