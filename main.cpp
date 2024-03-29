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
class MutantStack : public ft::stack<T> {
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
		typedef typename ft::stack<T>::container_type::reverse_iterator reverse_iterator;

		iterator			begin() { return this->c.begin(); }
		iterator			end() { return this->c.end(); }
		reverse_iterator	rbegin() { return this->c.rbegin(); }
		reverse_iterator	rend() { return this->c.rend(); }
};

template<class T>
void	swap(MutantStack<T> &x, MutantStack<T> &y) { x.swap(y) ;}

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
		std::cout << "vector_buffer capacity = " << vector_buffer.capacity() 
				<< ", vector_buffer size = " << vector_buffer.size() << std::endl;
		std::cout << "Empty vector_buffer tested succesfully !" << std::endl;	//NORMAL ! :P
	}
	std::cout << std::endl << "filling int vector test :" << std::endl;
	for (int i = 0; i < 500; i++) {
		vector_int.push_back(i);
	}
	std::cout << std::endl << "int vector filling sucesfully tested !" << std::endl;
	std::cout << "vector_int, size 500 : ";
	for (int i = 0; i < 500; i++) {
		std::cout << vector_int[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "at member function test at 305th place : " << vector_int.at(305) << std::endl;

	ft::vector<int> vector_neg_int;
	for (int i = 0; i < 500; i++) {
		vector_neg_int.push_back(-i);
	}
	std::cout << "vector_neg_int, size 500 : ";
	for (int i = 0; i < 500; i++) {
		std::cout << vector_neg_int[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "vector_int capacity = " << vector_int.capacity() 
				<< ", vector_int size = " << vector_int.size() << std::endl;
	std::cout << "vector_neg_int capacity = " << vector_neg_int.capacity() 
				<< ", vector_neg_int size = " << vector_neg_int.size() << std::endl;

	std::cout << "vector swap test :" << std::endl;		// swap testing
	swap(vector_int, vector_neg_int);
	std::cout << "vector_int after swapping with vector_neg_int : ";
	for (int i = 0; i < 500; i++) {
		std::cout << vector_int[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "vector_neg_int after swapping with vector_int : ";
	for (int i = 0; i < 500; i++) {
		std::cout << vector_neg_int[i] << " ";
	}
	std::cout << std::endl;

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

	std::cout << "find function test with a copied map :" << std::endl;
	{
		ft::map<int, int> copy = map_int;
		ft::map<int, int>::iterator find42 = copy.find(42);
		std::cout << "find 42 in the copied map container : "; 
		if (find42->first == 42)
			std::cout << "OK";
		else
			std::cout << "KO";
		std::cout << std::endl;
	}
	std::cout << std::endl << "##### Stack testing #####" << std::endl; 
	MutantStack<char> iterable_stack, reverse_iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	std::cout << "normally print the full alphabet :" << std::endl;
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl;

	for (char letter = 'z'; letter >= 'a'; letter--) {
		reverse_iterable_stack.push(letter);
	}
	std::cout << "normally print the full alphabet reversed : " << std::endl;
	for (MutantStack<char>::iterator it = reverse_iterable_stack.begin(); it != reverse_iterable_stack.end(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl;
	std::cout << "normally print the full alphabet with reverse_iterator : " << std::endl;
	for (MutantStack<char>::reverse_iterator it = reverse_iterable_stack.rbegin(); it != reverse_iterable_stack.rend(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl << std::endl;

	std::cout << "Stack manipulation tests :" << std::endl;
	iterable_stack.push('a');
	std::cout << "added a to the end iterable_stack :" << std::endl;
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl;
	iterable_stack.pop();
	std::cout << "popped the element from iterable_stack :" << std::endl;
	std::cout << "now the top of this stack element is : " << iterable_stack.top() << std::endl;
	return (0);
}