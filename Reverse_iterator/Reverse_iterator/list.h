#pragma once
#include"Reverse_iterator.h"
namespace ws
{
	template<class T>
	struct ListNode
	{

		ListNode(const T& val = T())
			:_prev(nullptr)
			,_next(nullptr)
			,_val(val)
		{}

		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _val;
	};

	// Ref -> reference 引用 T&
	// Ptr -> pointer 指针 T*
	template<class T, class Ref, class Ptr>
	struct list_iterator
	{
		typedef ListNode<T> Node;
		typedef list_iterator<T, Ref, Ptr> Self;

		Node* _node;// 封装在
		list_iterator(Node* node)
			:_node(node)
		{}

		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Ref operator*()
		{
			return _node->_val;
		}

		Ptr operator->()
		{
			return &_node->_val;
		}

		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}


	};

	template<class T>
	class list
	{
	public:
		typedef ListNode<T> Node;
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		
		typedef ReverseIterator<iterator, T&, T*> reverse_iterator;
		typedef ReverseIterator<const_iterator, const T&, const T*> const_reverse_iterator;
	public:

		iterator begin()
		{
			return _head->_next;
		}

		iterator end()
		{
			return _head;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_iterator begin() const
		{
			return _head->_next;
		}

		const_iterator end() const
		{
			return _head;
		}

		void empty_init()
		{
			_head = new Node;
			_head->_prev = _head;
			_head->_next = _head;
			_size = 0;
		}
		list()
		{
			empty_init();
		}

		// lt2(lt1)
		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}


		// lt1 = lt3
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		// 需要析构，一般就需要自己写深拷贝
		// 不需要析构，一般就不需要自己写深拷贝，默认浅拷贝就可以
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}


		void swap(list<T>& ls)
		{
			std::swap(_head, ls._head);
			std::swap(_size, ls._size);
		}

		void insert(iterator pos, const T& val)
		{
			Node* newnode = new Node(val);
			Node* cur = pos._node->_prev;
			Node* end = cur->_next;

			newnode->_next = end;
			newnode->_prev = cur;
			cur->_next = newnode;
			end->_prev = newnode;

			_size++;
		}

		iterator erase(iterator pos)
		{
			Node* start = pos._node->_prev;
			Node* end = pos._node;
			Node* next = pos._node->_next;
			start->_next = end->_next;
			end->_next->_prev = end->_prev;
			delete end;
			_size--;
			return iterator(next);
		}

		size_t size() const
		{
			return _size;
		}

		bool empty()
		{
			return _size == 0;
		}



	private:
		Node* _head = nullptr;
		size_t _size = 0;
	};
	
	
	void print_list(const list<int>& lt)
	{
		for (auto& it : lt)
		{
			std::cout << it << " ";
		}
		std::cout << std::endl;
	}
}