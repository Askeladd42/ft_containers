/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:52:00 by plam              #+#    #+#             */
/*   Updated: 2023/01/06 21:00:01 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_TPP__
# define __MAP_TPP__

# include <iostream>
# include <functional>
# include <memory>
# include "../utils/iterator.hpp"
# include "../utils/pair.hpp"
# include "../utils/algo.hpp"

namespace ft {
/* map container implementation
** ressources : https://cplusplus.com/reference/map/map/
**				https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
**				Introduction to Algorithms, Third Edition (2009)
**				(red-black tree algorithm)
*/

	/* Forward declarations */
	template<class T>
	struct rb_iterator;

	template<class T>
	struct rb_const_iterator;

	template<class T>
	struct rb_reverse_iterator;

	template<class T>
	struct rb_const_reverse_iterator;


	enum rb_color {RB_COLOR_BLACK = 1, RB_COLOR_RED, RB_COLOR_SENTINEL, RB_COLOR_NULL};

	/* Internal struct representing a binary tree node */
	template< class T, class Alloc = std::allocator<T> >
	struct rb_node {
		typedef T												value_type;
		typedef typename ft::rb_node<T>							node_type;
		typedef Alloc											allocator_type;
		typedef typename std::allocator<node_type>				node_allocator_type;
		typedef typename node_allocator_type::reference			reference;
		typedef typename node_allocator_type::const_reference	const_reference;
		typedef typename node_allocator_type::pointer			pointer;
		typedef typename node_allocator_type::const_pointer		const_pointer;
		typedef typename std::size_t							size_type;

		value_type	data;
		pointer		parent;
		pointer		left;
		pointer		right;
		int			color;

		/* Default constructor :
		** Constructs a new empty node with default value_type() and all
		** pointers to NULL.
		**
		** Color is always set to RED as
		** it will always be inserted as a RED node.
		*/
		rb_node() : data(value_type()), parent(NULL), left(NULL), right(NULL), color(RB_COLOR_RED) { }

		/* Data constructor :
		**
		** Constructs a new node with data and all pointers to NULL.
		**
		** Color is always set to RED as
		** it will always be inserted as a RED node.
		**
		*/
		rb_node(const value_type &__data) : data(__data), parent(NULL),
					left(NULL), right(NULL), color(RB_COLOR_RED) { }

		/* Data-Parent constructor function :
		** Constructs a new node with data and a parent, right and left
		** pointers are set to NULL.
		**
		** Color is always set to RED as
		** it will always be inserted as a RED node.
		*/
		rb_node(const value_type &__data, pointer __parent) :
					data(__data), parent(__parent), left(NULL), right(NULL), color(RB_COLOR_RED) { }

		/* grand parent pointer function :
		** Returns the grand parent of the current node.
		*/
		pointer	grand_parent() {
			if (this->parent == NULL)
				return NULL;
			return this->parent->parent;
		}

		/* uncle pointer function :
		** Returns the uncle node of the current node.
		*/
		pointer	uncle() {
			pointer gp = this->grand_parent();

			if (gp == NULL)
				return NULL;
			return this->parent->sibling();
		}

		/* sibling pointer function :
		** Uses rb_node and
		** returns the sibling node.
		*/
		pointer	sibling() {
			if (this->parent == NULL)
				return NULL;
			if (this == this->parent->left)
				return this->parent->right;
			return this->parent->left;
		}

		bool	is_sentinel() const {
			return (color == RB_COLOR_SENTINEL);
		}

		bool	is_left() const {
			if (this->parent == NULL)
				return false;
			return (this->parent->left == this);
		}

		bool	is_right() const {
			if (this->parent == NULL)
				return false;
			return (this->parent->right == this);
		}

		bool	is_null_node() const {
			return (this->color == RB_COLOR_NULL);
		}

		void	set_left(pointer node) {
			this->left = node;
			node->parent = this;
		}

		void	set_right(pointer node) {
			this->right = node;
			node->parent = this;
		}

		void	detach() {				// bad bracket closure to fix here
			if (this->parent) {
				if (this->is_left())
					this->parent->left = NULL;
				else
					this->parent->right = NULL;
				this->parent = NULL;
			}
		}

		void	assign(pointer node) {
			if (node) {
				this->parent = node->parent;
				this->color = node->color;
				this->set_left(node->left);
				this->set_right(node->right);
			}
		}
		
		size_type	max_size() const {
			return node_allocator_type().max_size();
		}

		class Compare {
			private:
				pointer	_node;
			public:
			Compare(pointer node) : _node(node) { }
			Compare(const Compare &comp) : _node(comp._node) { }
			Compare	&operator=(const Compare &comp) {
				_node = comp._node;
				return *this;
			}
			bool	operator()(pointer node) const {
				return _node == node;
			}
		};

		static Compare	create_compare(pointer node) {
			return Compare(node);
		}

		static pointer	create_node(node_allocator_type alloc = node_allocator_type()) {
			pointer node = alloc.allocate(1);

			alloc.construct(node, rb_node());
			return node;
		}

		static pointer	create_node(const value_type &data, node_allocator_type alloc = node_allocator_type()) {
			pointer	node = alloc.allocate(1);

			alloc.construct(node, data);
			return node;
		}

		static pointer	create_node(const value_type &data, pointer parent, node_allocator_type alloc = node_allocator_type()) {
			pointer	node = alloc.allocate(1);

			alloc.construct(node, rb_node(data, parent));
			return node;
		}

		static pointer	create_sentinel_node(node_allocator_type alloc = node_allocator_type()) {
			pointer node = rb_node::create_node(alloc);

			node->color = RB_COLOR_SENTINEL;
			return node;
		}

		static pointer	create_null_node(pointer parent, node_allocator_type alloc = node_allocator_type()) {
			pointer node = rb_node::create_node(alloc);

			node->color = RB_COLOR_BLACK;
			node->parent = parent;
			node->left = NULL;
			node->right = NULL;
			return node;
		}

		static pointer	create_null_node(node_allocator_type alloc = node_allocator_type()) {
			pointer node = rb_node::create_node(alloc);

			node->color = RB_COLOR_BLACK;
			return node;
		}

		/* Destroy node function :
		** Call the delete operator of the node and deallocate its memory.
		*/
		static void	destroy_node(pointer node, node_allocator_type alloc = node_allocator_type()) {
			if (node != NULL) {
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				node = NULL;
			}
		}
	};


	/* Map container :
	** Maps are associative containers that store elements formed by a combination of a
	** key value and a mapped value, following a specific order.
	**
	** In a map, the key values are generally used to sort and uniquely identify the elements,
	** while the mapped values store the content associated to this key. The types of key and
	** mapped value may differ, and are grouped together in member type value_type, which is
	** a pair type combining both:
	**
	** typedef pair<const Key, T> value_type;
	**
	** Internally, the elements in a map are always sorted by its key following a specific strict
	** weak ordering criterion indicated by its internal comparison object (of type Compare).
	**
	** map containers are generally slower than unordered_map containers to access individual
	** elements by their key, but they allow the direct iteration on subsets based on their order.
	**
	** The mapped values in a map can be accessed directly by their corresponding
	** key using the bracket operator ((operator[]).
	**
	** Maps are typically implemented as binary search trees, so that's why we use
	** a red-black tree structure for it here.
	*/
	template<
		class Key,												// map::key_type, the first template parameter
		class T,												// map::mapped_type, the second one
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<ft::pair<const Key, T> >	// map::allocator_type
	>
	class map {
		public:
			typedef Key																		key_type;
			typedef T																		mapped_type;
			typedef ft::pair<const key_type, mapped_type>									value_type;
			typedef Compare																	key_compare;
			typedef Alloc																	allocator_type;
			typedef typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::pointer										pointer;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef std::ptrdiff_t															difference_type;
			typedef std::size_t																size_type;
			typedef rb_iterator<value_type>													iterator;
			typedef rb_const_iterator<value_type>											const_iterator;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					Compare _comp;
					value_compare(Compare comp) : _comp(comp) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type &x, const value_type &y) const {
						return _comp(x.first, y.first);
					}
			};
		
		private:
			typedef rb_node<value_type>			node_type;
			typedef typename node_type::pointer	node_pointer;

		/* Member variables */
		private:
			node_pointer						_root;
			size_type							_size;
			key_compare							_comp;
			allocator_type						_alloc;
			node_pointer						_right_sentinel;
			node_pointer						_left_sentinel;
			node_pointer						_null;
			typename node_type::Compare			_is_null_node;

		/* Public member functions */
		public:
			/* default map constructor
			** (1) empty container constructor
			** Constructs an empty container, with no elements.
			*/
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				:	_root(NULL), _size(0), _comp(comp), _alloc(alloc),
					_right_sentinel(node_type::create_sentinel_node()),
					_left_sentinel(node_type::create_sentinel_node()),
					_null(node_type::create_null_node()),
					_is_null_node(node_type::create_compare(_null)) { }

			/* map constructor
			** (2) range constructor
			** Constructs a container with as many elements as the range [first,last), with each element constructed from its
			** corresponding element in that range.
			*/
			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				:	_root(NULL), _size(0), _comp(comp), _alloc(alloc),
					_right_sentinel(node_type::create_sentinel_node()),
					_left_sentinel(node_type::create_sentinel_node()),
					_null(node_type::create_null_node()),
					_is_null_node(node_type::create_compare(_null))
			{
				for (; first != last; ++first) {
					insert(*first);
				}
			}

			/* copy map constructor
			** (3) copy constructor
			** Constructs a container with a copy of each of the elements in x.
			*/
			map(const map &x) :
				_root(NULL), _size(0), _comp(x._comp), _alloc(x._alloc),
				_right_sentinel(node_type::create_sentinel_node()),
				_left_sentinel(node_type::create_sentinel_node()),
				_null(node_type::create_null_node()),
				_is_null_node(node_type::create_compare(_null))
			{
				/* Copy with breath first search, to get rid of rebalancing ?
				** When x is copied, the traversal will be in order,
				** that will cause rebalancing.
				*/
				this->insert(x.begin(), x.end());
			}

			/* Copy container content operator :
			** Assigns new contents to the container, replacing its current content.
			**
			** Copies all the elements from x into the container, changing its size accordingly.
			**
			** The container preserves its current allocator, which is used to allocate additional storage if needed.
			*/
			map &operator=(const map &x) {
				if (this != &x) {
					this->clear();		// Delete previous content
					_comp = x._comp;	// copy the content from the other map
					this->insert(x.begin(), x.end());
				}
				return *this;
			}
			/* default destructor function */
			~map() {
				clear();
				node_type::destroy_node(_right_sentinel);
				node_type::destroy_node(_left_sentinel);
				node_type::destroy_node(_null);
			}

			/* Insert function :
			** Extends the container by inserting new elements, effectively increasing the container 
			** size by the number of elements inserted.
			**
			** Because element keys in a map are unique, the insertion operation checks whether each 
			** inserted element has a key equivalent to the one of an element already in the container, 
			** and if so, the element is not inserted, returning an iterator to this existing element 
			** (if the function returns a value).
			**
			** For a similar container allowing for duplicate elements, see multimap.
			**
			** An alternative way to insert elements in a map is by using member function map::operator[].
			**
			** Internally, map containers keep all their elements sorted by their key following the criterion 
			** specified by its comparison object. The elements are always inserted in its respective position 
			** following this ordering.
			*/
			ft::pair<iterator, bool> insert(const value_type &val) {
				ft::pair<iterator, bool> ret;

				if (_root == NULL) {
					_size++;
					_root = node_type::create_node(val);
					_root->set_right(_right_sentinel);
					_root->set_left(_left_sentinel);
					return ft::pair<iterator, bool>(iterator(_root), true);
				}
				ret = insert_recursive_(_root, val);
				if (ret.second) {
					_size++;
					this->rb_insert_fix_tree_(ret.first._ptr);
				}
				return ret;
			}

			template<class InputIterator>
			void		insert(InputIterator first, InputIterator last) {
				for (; first != last; ++first) {
					this->insert(*first);
				}
			}

			iterator	insert(iterator position, const value_type &val) {
				iterator					curr = position;
				iterator					next = position;
				ft::pair<iterator, bool>	result;

				// If the position point to the end, insert normally
				if (size() == 0 || position == this->end() || position == (--this->begin())) {
					return this->insert(val).first;
				}
				// Otherwise, try another strategy, check that the val is within the range (position, position + 1)
				// until a valid range is found, where node will be inserted.
				// Check if greater or lower to determine the direction
				if (is_equal_val_(*position, val)){
					return position;
				}
				if (this->value_comp()(*position, val)) {
					// Go to right
					while (next != this->end()) {
						curr = next++;
						
						// Not found, insert at the end
						if (next == this->end())
							break;
						if (is_equal_val_(*curr, val))
							return curr;
						if (this->value_comp()(*curr, val) && this->value_comp()(val, *next))
							break;
					}
				}
				else {
					// Go to left
					while (next != this->begin()){
						curr = next--;
						
						// Not found, insert at the end
						if (next == this->begin())
							break;
						if (is_equal_val_(*curr, val))
							return curr;
						if (this->value_comp()(val, *curr) && this->value_comp()(*next, val))
							break;
					}
				}
				result = insert_recursive_(curr._ptr, val);
				if (result.second)
					_size++;
				return result.first;
			}

			/* Access operator :
			** If k matches the key of an element in the container, the function returns a reference to its mapped value.
			** If k does not match the key of any element in the container, the function inserts a new element with that
			** key and returns a reference to its mapped value. Notice that this always increases the container size by
			** one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).
			** A similar member function, map::at, has the same behavior when an element with the key exists, 
			** but throws an exception when it does not.
			*/
			mapped_type& operator[](const key_type& k) {
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}

			/* Clear map content :
			** Removes all elements from the map container (which are destroyed),
			** leaving the container with a size of 0.
			*/
			void clear() {
				if (_root) {
					clear_recursive_(_root);
					_root = NULL;
				}
				_size = 0;
			}

			/* find the iterator to the element :
			** Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
			** otherwise it returns an iterator to map::end.
			**
			** Two keys are considered equivalent if the container's comparison object returns false reflexively 
			** (i.e., no matter the order in which the elements are passed as arguments).
			** Another member function, map::count, can be used to just check whether a particular key exists.
			*/
			iterator		find(const key_type &k) {
				iterator found = this->lower_bound(k);

				return (found == this->end() || (_comp(k, (*found).first))) ? this->end() : found;
			}

			/* find the iterator to the element :
			** same than previously, but for const_iterators
			*/
			const_iterator	find(const key_type &k) const {
				const_iterator found = this->lower_bound(k);

				return ( found == this->end() || (_comp(k, (*found).first))) ? this->end() : found;
			}

			/* Erase function :
			** Removes from the map container either a single element or a range of elements ([first,last)).
			**
			** This effectively reduces the container size by the number of elements removed, which are destroyed.
			*/
			void	erase(iterator position) {
				if (position != this->end()) {
					node_pointer	target = position._ptr;
					node_pointer	successor;
					int				prev_color = target->color;
					bool			is_root = target == _root;

					if ( target->left != NULL && target->right != NULL ){
						// Case 3, node has children
						// Go to the right subtree, then find the min (go to leftmost)
						if ( target->left->is_sentinel() && target->right->is_sentinel() ){
							_root = NULL;
							successor = NULL;
						} else {
							ft::pair<node_pointer, int> ret = detach_node_(target);

							prev_color = ret.second;
							successor = (!is_root) ? ret.first : _root;
						}
					}
					else if ( target->left != NULL || target->right != NULL){
						// Case 2, target has one child
						successor = (target->right != NULL) ? target->right : target->left;

						if ( target->is_left() ){
							target->parent->set_left(successor);
						} else {
							target->parent->set_right(successor);
						}
						if ( successor->is_sentinel() )
							successor = target->parent;
					}
					else {
						// Case 1, target has no children
						_null->parent = target->parent;
						successor = _null;
						if ( target->is_left() ){
							target->parent->left = _null;
						} else {
							target->parent->right = _null;
						}
					}
					node_type::destroy_node( target );
					_size--;
					if ( _root != NULL && !_root->left->is_sentinel() && !_root->right->is_sentinel() &&
						prev_color == RB_COLOR_BLACK ){
							this->rb_erase_fix_(successor);
					}
					_null->detach();
				}
			}

			/* Erase function (range version) :
			** Removes from the map container either a single element or a range of elements ([first,last)).
			**
			** This effectively reduces the container size by the number of elements removed, which are destroyed.
			*/
			size_type	erase(const key_type &k) {
				iterator it = this->find( k );

				if (it == this->end())
					return 0;
				this->erase(it);
				return 1;
			}

			/* Erase function (range version) :
			** Removes from the map container either a single element or a range of elements ([first,last)).
			**
			** This effectively reduces the container size by the number of elements removed, which are destroyed.
			*/
			void	erase(iterator first, iterator last) {
				while (first != last)
					this->erase((*first++).first);
			}

			/* Swap function :
			** Exchanges the content of the container by the content of x, which is another map of the same type. 
			** Sizes may differ.
			**
			** After the call to this member function, the elements in this container are those which were in x 
			** before the call, and the elements of x are those which were in this.
			** All iterators, references and pointers remain valid for the swapped objects.
			**
			** Notice that a non-member function exists with the same name, swap, overloading that algorithm 
			** with an optimization that behaves like this member function.
			*/
			void	swap(map &x) {
				node_pointer				tmp_root = x._root;
				size_type					tmp_size = x._size;
				key_compare					tmp_comp = x._comp;
				allocator_type				tmp_alloc = x._alloc;
				node_pointer				tmp_right_sentinel = x._right_sentinel;
				node_pointer				tmp_left_sentinel = x._left_sentinel;
				typename node_type::Compare	tmp_is_null_node = x._is_null_node;

				x._root = this->_root;
				x._size = this->_size;
				x._comp = this->_comp;
				x._alloc = this->_alloc;
				x._right_sentinel = this->_right_sentinel;
				x._left_sentinel = this->_left_sentinel;
				x._is_null_node = this->_is_null_node;
				
				this->_root = tmp_root;
				this->_size = tmp_size;
				this->_comp = tmp_comp;
				this->_alloc = tmp_alloc;
				this->_right_sentinel = tmp_right_sentinel;
				this->_left_sentinel = tmp_left_sentinel;
				this->_is_null_node = tmp_is_null_node;
			}

			/* get container size function :
			** Returns the number of elements in the map container.
			*/
			size_type	size() const {
				return _size;
			}

			/* empty contaner tester function :
			** Returns whether the map container is empty (i.e. whether its size is 0).
			**
			** This function does not modify the container in any way. To clear the content of a map container, 
			** (cf map::clear)
			*/
			bool	empty() const {
				return _size == 0;
			}

			/* get maximum size function :
			** Returns the maximum number of elements that the map container can hold.
			**
			** This is the maximum potential size the container can reach due to known
			** system or library implementation limitations, but the container is by
			** no means guaranteed to be able to reach that size: it can still fail to
			** allocate storage at any point before that size is reached.
			*/
			size_type	max_size() const {
				return (node_type().max_size());
			}

			/* Return iterator to begining :
			** Returns an iterator referring to the first element in the map container
			** Because map containers keep their elements ordered at all times, begin points to the element that goes 
			** first following the container's sorting criterion
			** If the container is empty, the returned iterator value shall not be dereferenced.
			*/
			iterator	begin() {
				if (_root == NULL)
					return end();
				return iterator(_left_sentinel->parent);
			}

			/* Return iterator to begining
			** Same than previously, but for const_iterator
			*/
			const_iterator begin() const {
				if (_root == NULL)
					return end();
				return const_iterator(_left_sentinel->parent);
			}

			/* Return reverse iterator to reverse beginning :
			** Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			**
			** Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			**
			** rbegin points to the element preceding the one that would be pointed to by member end.
			*/
			reverse_iterator	rbegin() {
				if (_root == NULL)
					return rend();
				return reverse_iterator(end());
			}

			/* Return reverse iterator to reverse beginning :
			** Same than previously, but for const_iterator
			*/
			const_reverse_iterator rbegin() const {
				if (_root == NULL)
					return rend();
				return const_reverse_iterator(end());
			}

			/* Return iterator to end :
			** Returns an iterator referring to the past-the-end element in the map container.
			**
			** The past-the-end element is the theoretical element that would follow the last 
			** element in the map container. It does not point to any element, and thus shall not be dereferenced.
			**
			** Because the ranges used by functions of the standard library do not include the element pointed 
			** by their closing iterator, this function is often used in combination with map::begin to specify 
			** a range including all the elements in the container.
			**
			** If the container is empty, this function returns the same as map::begin.
			*/
			iterator		end() {
				return iterator(_right_sentinel);
			}

			/* Return iterator to end :
			** Same than previously, but for const_iterator
			*/
			const_iterator	end() const {
				return const_iterator(_right_sentinel);
			}

			/* Return reverse iterator to reverse end :
			**
			** Returns a reverse iterator pointing to the theoretical element right before the first element in the map container
			** (which is considered its reverse end).
			** The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).
			*/
			reverse_iterator rend() {
				return (reverse_iterator(begin()));
			}

			/* Return reverse iterator to reverse end :
			** Same than previously, but for const_iterator
			*/
			const_reverse_iterator rend() const {
				return (const_reverse_iterator(begin()));
			}


			/* Return iterator to upper bound
			**
			** Returns an iterator pointing to the first element in the container whose key is considered to go after k.
			** 
			** The function uses its internal comparison object (key_comp) to determine this, returning an iterator to 
			** the first element for which key_comp(k,element_key) would return true.
			**
			** If the map class is instantiated with the default comparison type (less), the function returns an iterator 
			** to the first element whose key is greater than k.
			**
			** A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the 
			** map contains an element with a key equivalent to k: In this case lower_bound returns an iterator pointing 
			** to that element, whereas upper_bound returns an iterator pointing to the next element.
			*/
			iterator	upper_bound(const key_type &k){
				node_pointer	y = NULL;
				node_pointer	x = _root;

				while (x != NULL && !x->is_sentinel()) {
					if (_comp(k, x->data.first)) {
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return (y == NULL) ? this->end() : iterator(y);
			}

			const_iterator	upper_bound(const key_type &k) const {
				node_pointer	y = NULL;
				node_pointer	x = _root;

				while (x != NULL && !x->is_sentinel()) {
					if (_comp(k, x->data.first)) {
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return (y == NULL) ? this->end() : const_iterator(y);
			}

			/* Return iterator to lower bound
			** 
			** Returns an iterator pointing to the first element in the container
			** whose key is not considered to go before k (i.e., either it is equivalent or goes after).
			**
			** The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the
			** first element for which key_comp(element_key,k) would return false.
			** If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is not less than k.
			** A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
			*/
			iterator		lower_bound(const key_type &k) {
				node_pointer	y = NULL;
				node_pointer	x = _root;

				while (x != NULL && !x->is_sentinel()) {
					if (!_comp(x->data.first, k)) {
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return (y == NULL) ? this->end() : iterator(y);
			}

			const_iterator	lower_bound(const key_type &k) const {
				node_pointer y = NULL;
				node_pointer x = _root;

				while (x != NULL && !x->is_sentinel()) {
					if (!_comp(x->data.first, k)) {
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return (y == NULL) ? this->end() : const_iterator(y);
			}

			/* Get range of equal elements
			**
			** Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
			**
			** Because the elements in a map container have unique keys, the range returned will contain a single element at most.
			**
			** If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element 
			** that has a key considered to go after k according to the container's internal comparison object (key_comp).
			**
			** Two keys are considered equivalent if the container's comparison object returns false reflexively 
			** (i.e., no matter the order in which the keys are passed as arguments).
			*/
			ft::pair<iterator, iterator> equal_range(const key_type& k) {
				return ft::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return ft::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k));
			}

			/* counter with a specific key :
			** Searches the container for elements with a key equivalent to k and returns the number of matches.
			**
			** Because all elements in a map container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
			** Two keys are considered equivalent if the container's comparison object returns false reflexively 
			** (i.e., no matter the order in which the keys are passed as arguments).
			*/
			size_type	count(const key_type &k) const {
				return this->find(k) != this->end();
			}

			/* Get allocator :
			** Returns a copy of the allocator object associated with the map.
			*/
			allocator_type	get_allocator() const {
				return _alloc;
			}

			/* Return value comparison object
			**
			** Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
			**
			** The arguments taken by this function object are of member type value_type (defined in map as an alias of pair<const key_type,mapped_type>),
			** but the mapped_type part of the value is not taken into consideration in this comparison.
			**
			** The comparison object returned is an object of the member type map::value_compare, which is a nested class that uses the internal comparison
			** object to generate the appropriate comparison functional class.
			**
			** The public member of this comparison class returns true if the key of the first argument is considered to go before that of the second 
			** (according to the strict weak ordering specified by the container's comparison object, key_comp), and false otherwise.
			** Notice that value_compare has no public constructor, therefore no objects can be directly created from this nested class outside map members.
			*/
			value_compare	value_comp() const {
				return value_compare(_comp);
			}

			/* Return key comparison object :
			** 
			** Returns a copy of the comparison object used by the container to compare keys.
			**
			** The comparison object of a map object is set on construction. Its type (member key_compare) is the third template parameter of the map template.
			** By default, this is a less object, which returns the same as operator<.
			**
			** This object determines the order of the elements in the container: it is a function pointer or a function object that takes two arguments of the
			** same type as the element keys, and returns true if the first argument is considered to go before the second in the strict weak ordering it defines,
			** and false otherwise.
			**
			** Two keys are considered equivalent if key_comp returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
			*/
			key_compare	key_comp() const {
				return _comp;
			}

		/* Private implementations: */
		private:
			/* Insert recursive :
			** 
			** Insert a node recursively. It returns a pair with an iterator
			** pointing to the node newly inserted.
			 */
			ft::pair<iterator, bool> insert_recursive_(node_pointer current, const value_type &val) {
				if (this->is_equal_key_(val.first, current->data.first))
					return ft::pair<iterator, bool>(iterator( current ), false);
				if (_comp( val.first, current->data.first)) {
					if (current->left == NULL)
						return ft::pair<iterator, bool>(iterator(current->left = node_type::create_node(val, current)), true);
					else if ( current->left->is_sentinel()) {
						node_pointer node = node_type::create_node(val, current);

						current->left = node;
						node->set_left(_left_sentinel);
						return ft::pair<iterator, bool>(iterator(node), true);
					}
					else
						return insert_recursive_(current->left, val);
				}
				else {
					if (current->right == NULL)
						return ft::pair<iterator, bool>(iterator(current->right = node_type::create_node( val, current)), true);
					else if (current->right->is_sentinel()) {
						node_pointer node = node_type::create_node(val, current);

						current->right = node;
						node->set_right(_right_sentinel);
						return ft::pair<iterator, bool>(iterator(node), true);
					}
					else
						return insert_recursive_(current->right, val);
				}
			}

			void	clear_recursive_(node_pointer current) {
				if (current != NULL && !current->is_sentinel() && !_is_null_node(current)) {
					clear_recursive_(current->left);
					clear_recursive_(current->right);
					node_type::destroy_node(current);
				}
			}

			ft::pair<node_pointer, int> detach_node_(node_pointer target) {
				node_pointer rightmost;
				node_pointer successor = target->right;
				ft::pair<node_pointer, int> ret;

				/* If the min node is a sentinel node, then take the left child
				** and set the sentinel node to the rightmost subtree.
				*/
				if (successor->is_sentinel()) {
					successor = target->left;
					successor->parent = target->parent;

					rightmost = successor;		// Go to the right most node and set right sentinel
					while (rightmost->right != NULL)
						rightmost = rightmost->right;
					ret.first = successor;
					ret.second = target->color;
					rightmost->set_right(_right_sentinel);
				}
				else {
					/* Find the left most child */
					while (successor->left != NULL && !successor->left->is_sentinel()) {
						successor = successor->left;
					}
					ret.first = successor->right;
					ret.second = successor->color;
					if (successor->parent == target) {
						successor->parent = target->parent;
						successor->set_left(target->left);
						ret.first = successor;
					}
					else {
						/* If successor node has a child, then set the successor parent
						** set this node as his new left child, otherwise, it is set to NULL.
						*/
						if (successor->right != NULL) {
							/* successor has a child case : */
							successor->parent->set_left(successor->right);
						} else {
							/* Successor is a leaf,
							** -> set to _null ?
							** successor->parent->left = NULL; */
							successor->parent->left = _null;
							_null->parent = successor->parent;
							ret.first = _null;
						}
						successor->assign(target);
					}
					successor->color = target->color;
				}
				/* Set the parent to point to the new successor, otherwise root is set to NULL. */
				if (target->parent != NULL) {
					if (target->is_left())
						target->parent->set_left(successor);
					else
						target->parent->set_right(successor);
				}
				else
					_root = successor;
				return ret;
			}

			void	rb_erase_fix_(node_pointer x) {
				node_pointer	s;

				while (x != _root && (x->color == RB_COLOR_BLACK || x->color == RB_COLOR_SENTINEL)) {
					if (x->is_left()){
						s = x->parent->right;
						if (s->color == RB_COLOR_RED) {
							s->color = RB_COLOR_BLACK;
							x->parent->color = RB_COLOR_RED;
							rb_rotate_left_(x->parent);
							s = x->parent->right;
						}
						if ((s->left == NULL || s->left->color == RB_COLOR_BLACK || s->is_sentinel()) &&
								(s->right == NULL || s->right->color == RB_COLOR_BLACK || s->is_sentinel())) {
							s->color = RB_COLOR_RED;
							x = x->parent;
						}
						else {
							if (s->right->color == RB_COLOR_BLACK) {
								s->left->color = RB_COLOR_BLACK;
								s->color = RB_COLOR_RED;
								rb_rotate_right_(s);
								s = x->parent->right;
							}
							s->color = x->parent->color;
							x->parent->color = RB_COLOR_BLACK;
							if (!s->right->is_sentinel())
								s->right->color = RB_COLOR_BLACK;
							rb_rotate_left_(x->parent);
							x = _root;
						}
					}
					else {
						s = x->parent->left;
						
						if (s->color == RB_COLOR_RED) {
							s->color = RB_COLOR_BLACK;
							x->parent->color = RB_COLOR_RED;
							rb_rotate_right_(x->parent);
							s = x->parent->left;
						}

						if (
							(s->left == NULL || s->left->color == RB_COLOR_BLACK || s->left->is_sentinel()) &&
							(s->right == NULL || s->right->color == RB_COLOR_BLACK || s->right->is_sentinel())) {
							s->color = RB_COLOR_RED;
							x = x->parent;
						}
						else {
							if (s->left->color == RB_COLOR_BLACK) {
								s->right->color = RB_COLOR_BLACK;
								s->color = RB_COLOR_RED;
								rb_rotate_left_(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = RB_COLOR_BLACK;
							if (!s->left->is_sentinel())
								s->left->color = RB_COLOR_BLACK;
							rb_rotate_right_(x->parent);
							x = _root;
						}
					}
				}
				if (!x->is_sentinel()) {
					x->color = RB_COLOR_BLACK;
				}
			}

			bool	is_equal_key_(const key_type &a, const key_type &b) {
				return !_comp(a, b) && !_comp(b, a);
			}

			bool	is_equal_val_(const value_type &a, const value_type &b) {
				return !_comp(a.first, b.first) && !_comp(b.first, a.first);
			}

			/* Red black tree utils */

			void	rb_insert_case_1_(node_pointer node) {
				if (node->parent == NULL)
					node->color = RB_COLOR_BLACK;
			}

			void	rb_insert_case_2_(node_pointer node) {
				(void)node;
				return ;
			}

			void	rb_insert_case_3_(node_pointer node) {
				node->parent->color = RB_COLOR_BLACK;
				node->uncle()->color = RB_COLOR_BLACK;

				node_pointer gp = node->grand_parent();
				gp->color = RB_COLOR_RED;
				rb_insert_fix_tree_(gp);
			}

			void	rb_insert_case_4_(node_pointer node) {
				node_pointer p = node->parent;
				node_pointer gp = node->grand_parent();

				if (gp != NULL) {
					if (gp->left != NULL && node == gp->left->right) {
						rb_rotate_left_(p);
						node = node->left;
					}
					else if (gp->right != NULL && node == gp->right->left) {
						rb_rotate_right_(p);
						node = node->right;
					}
					rb_insert_case_5_(node);
				}
			}

			void	rb_insert_case_5_(node_pointer node) {
				node_pointer p = node->parent;
				node_pointer gp = node->grand_parent();

				if (node->is_left())
					rb_rotate_right_(gp);
				else
					rb_rotate_left_(gp);
				p->color = RB_COLOR_BLACK;
				gp->color = RB_COLOR_RED;
			}

			void	rb_replace_sentinels_() {
				node_pointer leftmost = _root;
				node_pointer rightmost = _root;

				node_pointer lp = _left_sentinel->parent; // the leftmost element
				if (lp != NULL)
					lp->left = NULL;
				while (leftmost->left != NULL)
					leftmost = leftmost->left;
				leftmost->set_left(_left_sentinel);

				node_pointer rp = _right_sentinel->parent; // the rightmost element

				if (rp != NULL)
					rp->right = NULL;
				while (rightmost->right != NULL)
					rightmost = rightmost->right;
				rightmost->set_right(_right_sentinel);
			}

			void	rb_insert_fix_tree_(node_pointer node) {
				node_pointer uncle = node->uncle();

				if (node->parent == NULL)
					rb_insert_case_1_(node);
				else {
					if (node->parent->color == RB_COLOR_BLACK)
						rb_insert_case_2_(node);
					else if (uncle != NULL && uncle->color == RB_COLOR_RED)
						rb_insert_case_3_(node);
					else
						rb_insert_case_4_(node);
					rb_replace_sentinels_();
				}
			}

			void	rb_rotate_left_(node_pointer x) {
				node_pointer y = x->right;
				x->right = y->left;

				if (y->left != NULL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	rb_rotate_right_(node_pointer y) {
				node_pointer x = y->left;
				y->left = x->right;

				if (x->right != NULL)
					x->right->parent = y;
				x->parent = y->parent;
				if (y->parent == NULL)
					_root = x;
				else if (y == y->parent->right)
					y->parent->right = x;
				else
					y->parent->left = x;
				x->right = y;
				y->parent = x;
			}
	};

	template<class T>
	rb_node<T> *_rb_tree_decrement(rb_node<T> *ptr) {
		if (ptr->left != NULL) {
			ptr = ptr->left;
			while (ptr->right != NULL)
				ptr = ptr->right;
		}
		else {
			rb_node<T> *y = ptr->parent;
			while (ptr == y->left) {
				ptr = y;
				y = y->parent;
			}
			if (ptr->left != y)
				ptr = y;
		}
		return ptr;
	}

	template<class T>
	rb_node<T> *_rb_tree_increment(rb_node<T> *ptr) {
		if (ptr->right != NULL){
			ptr = ptr->right;
			while (ptr->left != NULL)
				ptr = ptr->left;
		}
		else {
			rb_node<T> *y = ptr->parent;
			while (ptr == y->right) {
				ptr = y;
				y = y->parent;
			}
			if (ptr->right != y)
				ptr = y;
		}
		return ptr;
	}

	template<class T>
	struct rb_iterator;

	template<class T>
	struct rb_const_iterator {
		typedef T								value_type;
		typedef const T&						reference;
		typedef const T*						pointer;

		typedef rb_iterator<T>					iterator;
		
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef rb_const_iterator<T>			_self;
		typedef rb_node<T>*						_base_ptr;
		typedef const rb_node<T>*				_link_type;

		/* Constructors */
		rb_const_iterator() : _ptr( NULL ) { }
		rb_const_iterator(_base_ptr ptr) : _ptr(ptr) { }
		rb_const_iterator(const iterator &it) : _ptr( it._ptr ) { }

		~rb_const_iterator() {}

		/* Accesses operators */
		reference	operator*() const {
			return _ptr->data;
		}
		pointer		operator->() const { return &_ptr->data; }

		/* Increment / Decrement operators */
		_self	&operator++() {
			_ptr = _rb_tree_increment(_ptr);
			return *this; 
		}

		_self	operator++(int) { 
			_self tmp = *this; 
			_ptr = _rb_tree_increment(_ptr); 
			return tmp; 
		}

		_self	&operator--() {
			_ptr = _rb_tree_decrement(_ptr);
			return *this;
		}
		_self	operator--(int) {
			_self tmp = *this;
			_ptr = _rb_tree_decrement(_ptr);
			return tmp;
		}

		/* Comparison operators */
		bool	operator!=(_self const &it) const { return _ptr != it._ptr; }
		bool	operator==(_self const &it) const { return _ptr == it._ptr; }
		
		_base_ptr	_ptr;
	};

	template<class T>
	struct rb_iterator {
		typedef T								value_type;
		typedef T&								reference;
		typedef T*								pointer;
		
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef rb_iterator<T>						_self;
		typedef rb_node<T>*						_base_ptr;
		typedef rb_node<T>*						_link_type;

		/* Constructors */
		rb_iterator() : _ptr( NULL ) { }
		rb_iterator(_base_ptr ptr) : _ptr(ptr) { }

		~rb_iterator() {}

		/* Accesses operators */
		reference	operator*() const 
		{ return _ptr->data; }

		pointer		operator->() const 
		{ return &_ptr->data; }

		/* Increment / Decrement operators */
		_self	&operator++() {
			_ptr = _rb_tree_increment(_ptr);
			return *this; 
		}

		_self	operator++(int) { 
			_self tmp = *this; 
			_ptr = _rb_tree_increment(_ptr); 
			return tmp; 
		}

		_self	&operator--() {
			_ptr = _rb_tree_decrement(_ptr);
			return *this;
		}
		_self	operator--(int) {
			_self tmp = *this;
			_ptr = _rb_tree_decrement(_ptr);
			return tmp;
		}

		/* Comparison operators */
		bool operator!=(_self const &it) const { return _ptr != it._ptr; }
		bool operator==(_self const &it) const { return _ptr == it._ptr; }
		
		_base_ptr	_ptr;
	};

	template<typename T>
	struct rb_reverse_iterator {
		typedef T								value_type;
		typedef T&								reference;
		typedef T*								pointer;
		
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef rb_reverse_iterator<T>			_self;
		typedef rb_node<T>*						_base_ptr;
		typedef const rb_node<T>*				_link_type;

		/* Constructors */
		rb_reverse_iterator() : _ptr( NULL ) { }
		rb_reverse_iterator(_base_ptr ptr) : _ptr(ptr) { }
		~rb_reverse_iterator() {}

		/* Accesses operators */
		reference	operator*() const 
		{ return _ptr->data; }

		pointer		operator->() const 
		{ return &_ptr->data; }

		/* Increment / Decrement operators */
		_self &operator++() {
			_ptr = _rb_tree_decrement(_ptr);
			return *this;
		}

		_self operator++(int) {
			_self tmp = *this;
			_ptr = _rb_tree_decrement(_ptr);
			return tmp;
		}

		_self &operator--() {
			_ptr = _rb_tree_increment(_ptr);
			return *this;
		}
		_self operator--(int) {
			_self tmp = *this;
			_ptr = _rb_tree_increment(_ptr);
			return tmp;
		}

		/* Comparison operators */
		bool	operator!=(_self const &it) const { return _ptr != it._ptr; }
		bool	operator==(_self const &it) const { return _ptr == it._ptr; }
		
		_base_ptr	_ptr;
	};

	template<typename T>
	struct rb_const_reverse_iterator {
		typedef T								value_type;
		typedef const T&						reference;
		typedef const T*						pointer;

		typedef rb_reverse_iterator<T>			iterator;
		
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef rb_const_reverse_iterator<T>	_self;
		typedef rb_node<T>*						_base_ptr;
		typedef const rb_node<T>*				_link_type;

		/* Constructors */
		rb_const_reverse_iterator() : _ptr( NULL ) { }
		rb_const_reverse_iterator(_base_ptr ptr) : _ptr(ptr) { }
		rb_const_reverse_iterator(const iterator &it) : _ptr( it._ptr ) { }
		~rb_const_reverse_iterator() {}

		/* Accesses operators */
		reference	operator*() const {
			return _ptr->data;
		}
		pointer		operator->() const { return &_ptr->data; }

		/* Increment / Decrement operators */
		_self	&operator++() {
			_ptr = _rb_tree_decrement(_ptr);
			return *this;
		}

		_self	operator++(int) {
			_self tmp = *this;
			_ptr = _rb_tree_decrement(_ptr); 
			return tmp;
		}

		_self &operator--() {
			_ptr = _rb_tree_increment(_ptr);
			return *this;
		}
		_self operator--(int) {
			_self tmp = *this;
			_ptr = _rb_tree_increment(_ptr);
			return tmp;
		}

		/* Comparison operators */
		bool operator!=(_self const &it) const { return _ptr != it._ptr; }
		bool operator==(_self const &it) const { return _ptr == it._ptr; }
		
		_base_ptr	_ptr;
	};

	/* swap function */
	template<class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
		x.swap(y);
	}

	/* comparison operator functions */

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y) {
		return (x.size() == y.size() && equal(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y) {
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y) {
		return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y) {
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y) {
		return (y < x);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y) {
		return !(x < y);
	}
}

#endif