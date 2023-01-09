#include <iostream>
#include <string>
#include <deque>
#ifdef FT
	#include "includes/map.hpp"
	#include "includes/stack.hpp"
	#include "includes/vector.hpp"
#else	//CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	std::cout << std::endl << "##### Vector testing #####" << std::endl;
	std::cout << std::endl << "Empty vector_buffer test :" << std::endl;
	
	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "Empty vector_buffer tested succesfully !" << std::endl;	//NORMAL ! :P
	}
	std::cout << std::endl << "filling int vector test :" << std::endl;
	for (int i = 0; i < 15; i++) {
		vector_int.push_back(i);
	}
	std::cout << "vector_int, size 15 : ";
	for (int i = 0; i < 15; i++) {
		std::cout << vector_int[i] << " ";
	}
	std::cout << std::endl << "int vector filling sucesfully tested !" << std::endl;

	std::cout << std::endl << "##### Map testing #####" << std::endl;
	std::cout << std::endl << "basic max_size testing :" << std::endl;
	if (map_int.max_size() > 1000) {
		for (int i = 0; i < 1000; i++)
			map_int[i] = 0;
		std::cout << "The map contains 1000 elements." << std::endl;
	}
	else
		std::cout << "The map could not hold 1000 elements." << std::endl;
	std::cout << std::endl << "basic testing :" << std::endl;
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	std::cout << std::endl << "##### Stack testing #####" << std::endl; 
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	std::cout << "normally print the full alphabet :" << std::endl;
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}