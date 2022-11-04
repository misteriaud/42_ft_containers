#pragma once
#ifndef RBTree_HPP
# define RBTree_HPP

#include <iostream>
#include <stack.hpp>
#include <memory>

typedef enum e_color {
	RED,
	BLACK
}		t_color;

#define NULL_NODE _sentinel
#define IS_NODE(node) (node && node != _sentinel)
#define SAME_KEY(a_value, b_value) (!_comp(a_value, b_value) && !_comp(b_value, a_value))
#define MIN _sentinel->left
#define MAX _sentinel->right
#define ROOT _sentinel->parent

namespace ft {

template<
	typename T
	>
class Node {
	public:
		typedef	T			value_type;
		typedef Node*		pointer;
		typedef const Node* const_pointer;
		typedef Node&		reference;
		typedef const Node&	const_reference;

		Node(
			value_type value = value_type(),
			t_color color = RED,
			const pointer sentinel = NULL
		)
			: value(value), color(color), parent(NULL), left(sentinel), right(sentinel), _sentinel(sentinel) {};
		Node(const_reference from):
			value(from.value), color(from.color), parent(from.parent), left(from.left), right(from.right), _sentinel(from._sentinel) {};
		~Node() {};

		// getters
		pointer	next() const {
			const_pointer curr = this;
			if (curr == MAX)
				return (_sentinel);
			if (!curr->is_node())
				return (left);
			if (right->is_node())
				return right->min();
			pointer tmp_parent = parent;
			while (tmp_parent->is_node() && curr == tmp_parent->right) {
				curr = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return (tmp_parent);
		}
		pointer	previous() const {
			const_pointer	curr = this;
			if (curr == MIN)
				return (NULL);
			if (!curr->is_node())
				return (right);
			if (left->is_node())
				return left->max();
			pointer tmp_parent = parent;
			while (tmp_parent->is_node() && curr == tmp_parent->left) {
				curr = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return (tmp_parent);
		}
		pointer min() {
			pointer curr = this;
			if (curr == _sentinel)
				return (curr);
			while(curr->left != _sentinel)
				curr = curr->left;
			return (curr);
		}
		pointer max() {
			pointer curr = this;
			if (curr == _sentinel)
				return (curr);
			while(curr->right != _sentinel)
				curr = curr->right;
			return (curr);
		}

		// setters
		pointer set_left(const pointer new_left) {
			if (is_node())
				left = new_left;
			return (left);
		}
		pointer set_right(const pointer new_right) {
			if (is_node())
				right = new_right;
			return (right);
		}
		pointer set_parent(const pointer new_parent) {
			if (is_node())
				parent = new_parent;
			return (parent);
		}
		pointer	set_min(const pointer new_min) {
			if (!is_node()) {
				left = new_min;
			}
			return (left);
		}
		pointer	set_max(const pointer new_max) {
			if (!is_node()) {
				right = new_max;
			}
			return (right);
		}
		pointer	set_root(const pointer new_root) {
			if (!is_node()) {
				parent = new_root;
			}
			return (parent);
		}

		// sentinel
		void	init_sentinel() {
			_sentinel = this;
			parent = this;
			left = this;
			right = this;
		}
		inline bool	is_node() const { return (this != _sentinel); }
		// operators
		bool		operator==(const_reference rhs) { return value == rhs.value; }
		bool		operator!=(const_reference rhs) { return value != rhs.value; }
		value_type&	operator*() { return value; }
		Node&		operator=(const Node& rhs) {
			if (this == &rhs)
				return (*this);
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			value = rhs.value;
			color = rhs.color;
			return (*this);
		}

		value_type			value;
		t_color				color;
		pointer				parent;
		pointer				left;
		pointer				right;
		pointer				_sentinel;

};

template<
	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>
	>
class RBTree {
	public:
		typedef	T											value_type;
		typedef typename Allocator::template rebind<Node<T> >::other	allocator_type;
		typedef std::size_t									size_type;
		typedef Node<T>										node_type;
		typedef node_type*									pointer;
		typedef RBTree&										reference;
		typedef const RBTree&								const_reference;
		typedef Compare										compare_type;

		RBTree(const compare_type& comp, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _comp(comp), _size(0), _sentinel(_alloc.allocate(1)) {
			_alloc.construct(_sentinel, Node<T>(T(), BLACK));
			_sentinel->init_sentinel();
		};
		RBTree(const_reference from): _comp(from._comp), _size(0), _sentinel(_alloc.allocate(1)) {
			_alloc.construct(_sentinel, Node<T>(T(), BLACK));
			_sentinel->init_sentinel();
			operator=(from);
		};
		~RBTree() {
			clear();
			while(!_available_mem.empty()) {
				_alloc.deallocate(_available_mem.top(), 1);
				_available_mem.pop();
			}
			_alloc.destroy(_sentinel);
			_alloc.deallocate(_sentinel, 1);
		};
		reference	operator=(const_reference rhs) {
			if (this == &rhs)
				return (*this);
			clear();
			_comp = rhs._comp;
			ROOT = copy_subtree(rhs.ROOT);
			MIN = ROOT->min();
			MAX = ROOT->max();
			_size = rhs._size;
			return (*this);
		}

		//
		// SEARCH AND TRAVERSAL
		//
		pointer	find(T value) {
			pointer curr = ROOT;
			while (IS_NODE(curr) && !SAME_KEY(**curr, value)) {
				if (_comp(value, **curr))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return (curr);
		}
		pointer lower_bound(T value) {
			pointer curr = ROOT;
			pointer prev = NULL_NODE;

			if (!_size || _comp(**MAX, value))
				return (NULL_NODE);
			else if (_comp(value, **MIN))
				return (MIN);
			while (IS_NODE(curr) && !SAME_KEY(**prev, value)) {
				prev = curr;
				if (_comp(value, **curr))
					curr = curr->left;
				else
					curr = curr->right;
			}
			if (SAME_KEY(**prev, value))
				return (prev);
			return (prev->next());
		}
		pointer upper_bound(T value) {
			pointer curr = ROOT;
			pointer prev = NULL_NODE;
			if (!_size || _comp(**MAX, value))
				return (NULL_NODE);
			else if (_comp(value, **MIN))
				return (MIN);
			while (IS_NODE(curr) && !SAME_KEY(**prev, value)) {
				prev = curr;
				if (_comp(value, **curr))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return (prev->next());
		}

		//
		// INSERTION
		//
		pointer insert(const T& value, const pointer hint = NULL) {
			pointer y = NULL_NODE;
			pointer temp = ROOT;

			if (!hint || !IS_NODE(hint) || !(_comp(**hint, value) && _comp(value, **(hint->next())))) {
				while(IS_NODE(temp)) {
					y = temp;
					if(SAME_KEY(**temp, value))
						return (temp);
					if(_comp(value, **temp))
						temp = temp->left;
					else
						temp = temp->right;
				}
			}
			else
				y = hint->right;

			pointer	new_node = create_node(Node<T>(value, RED, NULL_NODE));
			new_node->set_parent(y);

			if(!IS_NODE(y))
				ROOT = new_node;
			else if(_comp(**new_node, **y))
				y->set_left(new_node);
			else
				y->set_right(new_node);
			insertion_fixup(new_node);
			if (!IS_NODE(MIN) || _comp(**new_node, **MIN))
				MIN = new_node;
			if (!IS_NODE(MAX) || _comp(**MAX, **new_node))
				MAX = new_node;
			_size++;
			return (new_node);
		}
		void insertion_fixup(pointer z) {
			while(z->parent->color == RED) {
				if(z->parent == z->parent->parent->left) { //z.parent is the left child
					pointer y = z->parent->parent->right; //uncle of z
					if(y->color == RED) { //case 1
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else { //case2 or case3
						if(z == z->parent->right) { //case2
							z = z->parent; //marked z.parent as new z
							left_rotate(z);
						}
					//case3
						z->parent->color = BLACK; //made parent black
						z->parent->parent->color = RED; //made parent red
						right_rotate(z->parent->parent);
					}
				}
				else { //z.parent is the right child
					pointer y = z->parent->parent->left; //uncle of z

					if(y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else {
						if(z == z->parent->left) {
							z = z->parent; //marked z.parent as new z
							right_rotate(z);
						}
						z->parent->color = BLACK; //made parent black
						z->parent->parent->color = RED; //made parent red
						left_rotate(z->parent->parent);
					}
				}
			}
			ROOT->color = BLACK;
		}


		//
		// DELETION
		//
		size_type remove(const pointer z) {
			if (!IS_NODE(z))
				return (0);
			pointer	y = z;
			pointer	x;
			t_color	y_orignal_color = y->color;

			if (z == MIN)
				MIN = z->next();
			if (z == MAX)
				MAX = z->previous();
			if(!IS_NODE(z->left)) {
				x = z->right;
				transplant(z, z->right);
			}
			else if(!IS_NODE(z->right)) {
				x = z->left;
				transplant(z, z->left);
			}
			else {
				y = z->right->min();
				y_orignal_color = y->color;
				x = y->right;
				if(y->parent == z) {
					x->set_parent(y);
				}
				else {
					transplant(y, y->right);
					y->set_right(z->right);
					y->right->set_parent(y);
				}
				transplant(z, y);
				y->set_left(z->left);
				y->left->set_parent(y);
				y->color = z->color;
			}
			if(y_orignal_color == BLACK)
				remove_fixup(x);
			release_node(z);
			_size--;
			return (1);
		}

		/**
		 * @brief Transplant one branch at the place of an old node
		 *
		 * @param u the Node to be replace
		 * @param v the branch to be move
		 */
		void transplant(pointer u, pointer v) {
			// if(u == ROOT || u->parent == _sentinel)
			// if(!IS_NODE(u->parent))
			if(u == ROOT)
				ROOT = v;
			else if(u == u->parent->left)
				u->parent->set_left(v);
			else
				u->parent->set_right(v);
			if (IS_NODE(v))
				v->set_parent(u->parent);
		}

		void remove_fixup(pointer x) {
			while(IS_NODE(x) && x != ROOT && x->color == BLACK) {
				if(x == x->parent->left) {
					pointer w = x->parent->right;
					if(w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if(w->left->color == BLACK && w->right->color == BLACK) {
						w->color = RED;
						x = x->parent;
					}
					else {
						if(w->right->color == BLACK) {
							w->left->color = BLACK;
							w->color = RED;
							right_rotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						left_rotate(x->parent);
						x = ROOT;
					}
				}
				else {
					pointer w = x->parent->left;
					if(w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if(w->right->color == BLACK && w->left->color == BLACK) {
						w->color = RED;
						x = x->parent;
					}
					else {
						if(w->left->color == BLACK) {
							w->right->color = BLACK;
							w->color = RED;
							left_rotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						right_rotate(x->parent);
						x = ROOT;
					}
				}
			}
			x->color = BLACK;
		}


		void clear() {
			pointer curr = MIN;
			pointer tmp = NULL_NODE;
			if (empty())
				return ;
			while (IS_NODE(ROOT->left) || IS_NODE(ROOT->right)) {
				if (IS_NODE(curr->left))
					curr = curr->left;
				else if (IS_NODE(curr->right))
					curr = curr->right;
				else {
					tmp = curr;
					curr = curr->parent;
					if (tmp == curr->left)
						curr->set_left(NULL_NODE);
					else
						curr->set_right(NULL_NODE);
					release_node(tmp);
				}
			}
			release_node(curr);
			_sentinel->init_sentinel();
			_size = 0;
		}

		//
		// ROTATION
		//
		void	left_rotate(const pointer x) {
			pointer y = x->right;
			x->set_right(y->left);
			if (IS_NODE(y->left))
				y->left->set_parent(x);
			y->set_parent(x->parent);
			if (!IS_NODE(x->parent))
				ROOT = y;
			else if (x == x->parent->left)
				x->parent->set_left(y);
			else
				x->parent->set_right(y);
			y->set_left(x);
			x->set_parent(y);
		}

		void	right_rotate(const pointer x) {
			pointer y = x->left;
			x->set_left(y->right);
			if (IS_NODE(y->right))
				y->right->set_parent(x);
			y->set_parent(x->parent);
			if (!IS_NODE(x->parent))
				ROOT = y;
			else if (x == x->parent->right)
				x->parent->set_right(y);
			else
				x->parent->set_left(y);
			y->set_right(x);
			x->set_parent(y);
		}

		pointer	min() const {
			return (MIN);
		}
		pointer	max() const {
			return (MAX);
		}
		bool	empty() const {
			return (!_size);
		}
		size_type	size() const {
			return (_size);
		}
		size_type	max_size() const {
			return _alloc.max_size();
		}
		node_type*	sentinel() {
			return _sentinel;
		}

		// EXCEPTION
		class alreadyExist: public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("this key already exist");
				}
		};

	private:
		allocator_type		_alloc;
		compare_type		_comp;
		size_type			_size;
		ft::stack<pointer>	_available_mem;
		pointer				_sentinel;


		pointer copy_subtree(const pointer src, pointer p = NULL) {
			if (!p)
				p = NULL_NODE;
			if(src == src->_sentinel)
				return (_sentinel);
			pointer new_node = create_node(Node<T>(src->value, src->color, NULL_NODE));
			new_node->set_parent(p);
			if(src->left != src->_sentinel)
				new_node->set_left(copy_subtree(src->left, new_node));
			if(src->right != src->_sentinel)
				new_node->set_right(copy_subtree(src->right, new_node));
			return (new_node);
		}

		// MEMORY MANAGEMENT
		pointer	create_node(const Node<T>& ref) {
			pointer new_node;
			if (!_available_mem.empty()) {
				new_node = _available_mem.top();
				_available_mem.pop();
			}
			else
				new_node = _alloc.allocate(1);
			_alloc.construct(new_node, ref);
			return (new_node);
		}
		void	release_node(const pointer node) {
			_alloc.destroy(node);
			_available_mem.push(node);
		}
};
}

#endif
