#pragma once
#ifndef RBTree_HPP
# define RBTree_HPP

#include <iostream>
#include <stack>
#include <memory>

typedef enum {
	RED,
	BLACK
}		t_color;

#define NULL_NODE Node<T>::NIL()
#define IS_NODE(node) (node != Node<T>::NIL())

namespace ft {

template<typename T>
class Node {
	public:
		typedef	T			value_type;
		typedef Node*		pointer;
		typedef Node&		reference;
		typedef const Node&	const_reference;

		Node(value_type value = value_type(), t_color color = RED, const pointer NIL = NULL_NODE)
			: parent(NULL), left(NIL), right(NIL), value(value), color(color) {};
		Node(const_reference from): parent(from.parent), left(from.left), right(from.right), value(from.value), color(from.color) {};
		~Node() {
		};

		pointer min() {
			pointer curr = this;
			while(IS_NODE(curr->left))
				curr = curr->left;
			return (curr);
		}

		pointer max() {
			pointer curr = this;
			while(IS_NODE(curr->right))
				curr = curr->right;
			return (curr);
		}

		pointer	next() {
			pointer	curr = this;
			if (IS_NODE(right))
				return right->min();
			pointer tmp_parent = parent;
			while (IS_NODE(tmp_parent) && curr == tmp_parent->right) {
				curr = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return (tmp_parent);
		}

		pointer	previous() {
			pointer	curr = this;
			if (IS_NODE(left))
				return right->max();
			pointer tmp_parent = parent;
			while (IS_NODE(tmp_parent) && curr == tmp_parent->left) {
				curr = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return (tmp_parent);
		}

		void	print_label(unsigned int uuid, pointer focus) {
			std::cout << "\t" << uuid << reinterpret_cast<long long>(this) << " [label=<";
			if (this == focus)
				std::cout << "<U>" << value << "</U>";
			else
				std::cout << value;
			std::cout << ">, color=" << (color == RED ? "\"red\"];\n" : "\"black\"];\n");
			if (IS_NODE(left))
				left->print_label(uuid, focus);
			if (IS_NODE(right))
				right->print_label(uuid, focus);
		}

		void	print_childs(unsigned int uuid) {
			if (IS_NODE(left)) {
				left->print_childs(uuid);
				std::cout << "\t" << uuid << reinterpret_cast<long long>(this) << " -> " << uuid <<reinterpret_cast<long long>(left) << ";" << std::endl;
			}
			if (IS_NODE(right)) {
				std::cout << "\t" << uuid << reinterpret_cast<long long>(this) << " -> " << uuid <<reinterpret_cast<long long>(right) << ";" << std::endl;
				right->print_childs(uuid);
			}
		}

		bool		operator==(const reference rhs) { return value == rhs.value; }
		bool		operator!=(const reference rhs) { return value != rhs.value; }
		bool		operator<(const reference rhs) { return value < rhs.value; }
		bool		operator>(const reference rhs) { return value > rhs.value; }

		value_type	operator*() { return value; }
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

		static pointer NIL() {
			static Node	sentinel(T(), BLACK, NULL);
			return &sentinel;
		};

		pointer				parent;
		pointer				left;
		pointer				right;
		value_type			value;
		t_color				color;
};

template<
	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>
	>
class RBTree {
	public:
		typedef	T											value_type;
		typedef typename Allocator::rebind<Node<T>>::other	allocator_type;
		typedef std::size_t									size_type;
		typedef Node<T>*									pointer;
		typedef RBTree&										reference;
		typedef const RBTree&								const_reference;

		RBTree(const allocator_type& alloc = allocator_type()): _alloc(alloc), _root(NULL_NODE), _min(_root), _max(_root), _size(0) {};
		RBTree(const_reference from) { *this = from; }
		~RBTree() {
			clear();
			while(!_available_mem.empty()) {
				_alloc.deallocate(_available_mem.top(), 1);
				_available_mem.pop();
			}
		};
		reference	operator=(const reference rhs) {
			if (this == &rhs)
				return (*this);
			clear();
			_alloc = rhs._alloc;
			_root = copy_subtree(rhs._root);
			_min = _root->min();
			_max = _root->max();
			_size = rhs._size;
			return (*this);
		}

		//
		// SEARCH AND TRAVERSAL
		//
		template<typename Ret>
		Ret	forEach(Ret (func)(T)) {
			pointer curr = _min();
			while (curr)
			{
				func(**curr);
				curr = curr->next();
			}
		}
		pointer	find(T value) {
			pointer curr = _root;
			while (IS_NODE(curr) && **curr != value) {
				if (value < **curr)
					curr = curr->left;
				else
					curr = curr->right;
			}
			return (!IS_NODE(curr) ? NULL : curr);
		}


		//
		// INSERTION
		//
		void insert(T value) {
			pointer y = NULL_NODE;
			pointer temp = _root;

			while(IS_NODE(temp)) {
				y = temp;
				if(**temp == value)
					throw alreadyExist();
				if(value < **temp)
					temp = temp->left;
				else
					temp = temp->right;
			}

			pointer	new_node = create_node(Node(value, RED));
			new_node->parent = y;

			if(!IS_NODE(y))
				_root = new_node;
			else if(*new_node < *y)
				y->left = new_node;
			else
				y->right = new_node;
			insertion_fixup(new_node);
			if (!IS_NODE(_min) || *new_node < *_min)
				_min = new_node;
			if (!IS_NODE(_max) || *new_node > *_max)
				_max = new_node;
			_size++;
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
			_root->color = BLACK;
		}


		//
		// DELETION
		//
		void rb_delete(T value) {
			pointer z = find(value);
			if (!z)
				return;
			pointer	y = z;
			pointer	x;
			t_color	y_orignal_color = y->color;

			if (z == _min)
				_min = z->next();
			if (z == _max)
				_max = z->previous();
			if(!IS_NODE(z->left)) {
				x = z->right;
				rb_transplant(z, z->right);
			}
			else if(!IS_NODE(z->right)) {
				x = z->left;
				rb_transplant(z, z->left);
			}
			else {
				y = z->right->min();
				y_orignal_color = y->color;
				x = y->right;
				if(y->parent == z) {
					x->parent = z;
				}
				else {
					rb_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				rb_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if(y_orignal_color == BLACK)
				rb_delete_fixup(x);
			release_node(z);
			_size--;
		}

		void rb_transplant(pointer u, pointer v) {
			if(!IS_NODE(u->parent))
				_root = v;
			else if(u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void rb_delete_fixup(pointer x) {
			while(x != _root && x->color == BLACK) {
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
						x = _root;
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
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}


		void clear() {
			pointer curr = _min;
			pointer tmp = NULL_NODE;
			if (!_size)
				return ;
			while (IS_NODE(_root->left) || IS_NODE(_root->right)) {
				if (IS_NODE(curr->left))
					curr = curr->left;
				else if (IS_NODE(curr->right))
					curr = curr->right;
				else {
					tmp = curr;
					curr = curr->parent;
					if (tmp == curr->left)
						curr->left = NULL_NODE;
					else
						curr->right = NULL_NODE;
					release_node(tmp);
				}
			}
			release_node(curr);
			_size = 0;
		}

		//
		// ROTATION
		//
		void	left_rotate(const pointer x) {
			pointer y = x->right;
			x->right = y->left;
			if (IS_NODE(y->left))
				y->left->parent = x;
			y->parent = x->parent;
			if (!IS_NODE(x->parent))
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void	right_rotate(const pointer x) {
			pointer y = x->left;
			x->left = y->right;
			if (IS_NODE(y->right))
				y->right->parent = x;
			y->parent = x->parent;
			if (!IS_NODE(x->parent))
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		// PRINT
		void	print(pointer focus = NULL) {
			#ifdef PRINT
				static int uuid;
				ft::stack<pointer>	to_print;
				if (!IS_NODE(_root))
					return ;
				_root->print_label(uuid, focus);
				std::cout << std::endl;
				_root->print_childs(uuid);
				uuid++;
			#else
				(void)focus;
			#endif
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
		pointer				_root;
		pointer				_min;
		pointer				_max;
		size_type			_size;
		ft::stack<pointer>	_available_mem;

		pointer copy_subtree(const pointer src, const pointer p = NULL_NODE) {
			if(!IS_NODE(src))
				return (NULL_NODE);
			pointer new_node = create_node(Node(src->value, src->color));
			new_node->parent = p;
			if(IS_NODE(src->left))
				new_node->left = copy_subtree(src->left, new_node);
			if(IS_NODE(src->right))
				new_node->right = copy_subtree(src->right, new_node);
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
