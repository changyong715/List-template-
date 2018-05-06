#pragma once
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

template<class T>
struct ListNode {
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& data=T())
		:_data(data)
		, _next(NULL)
		, _prev(NULL)
	{}
};

template<class T>
class List {
	typedef ListNode<T> Node;
public:
	List()
		:_head(new Node(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	~List()
	{
		Clean();
		delete _head;
	}
	T& Back()
	{
		return _head->_prev->_data;
	}
	T& Front()
	{
		return _head->_next->_data;
	}
	void Clean()
	{
		Node* cur = _head->_next;
		Node* tmp = _head;
		while (cur != _head)
		{
			tmp = cur->_next;
			delete cur;
			cur = tmp;
		}
		cur = NULL;
	}
	void PushBack(const T& data);
	void PushFront(const T& data);
	void Insert(Node* pos, const T& data);
	void PopBack();
	void PopFront();
	void Erase(Node* pos);
	void Print();
	bool Empty();
	const Node* Find(const T& data)const
	{
		if (_head->_next == _head)
			return NULL;
		else
		{
			Node* cur = _head->_next;
			while (cur != _head)
			{
				if (cur->_data == data)
					return cur;
				cur = cur->_next;
			}
			return NULL;
		}
	}

protected:
	Node* _head;
};
template<class T>
void List<T>::Insert(Node* pos, const T& data)
{
	assert(pos);
	Node* node = new Node(data);
	Node* next = pos->_next;
	//链接四个指针
	node->_prev = pos;
	node->_next = next;
	next->_prev = node;
	pos->_next = node;
}

template<class T>
void List<T>::PushBack(const T& data)
{
	Insert(_head->_prev, data);
}

template<class T>
void List<T>::PushFront(const T& data)
{
	Insert(_head, data);
}

template<class T>
void List<T>::Print()
{
	Node* cur = _head->_next;
	while (cur != _head)
	{
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << endl;
}

template<class T>
void List<T>::Erase(Node* pos)
{
	assert(pos);
	pos->_prev->_next = pos->_next;
	pos->_next->_prev = pos->_prev;
}

template<class T>
void List<T>::PopBack()
{
	Erase(_head->_prev);
}

template<class T>
void List<T>::PopFront()
{
	Erase(_head->_next);
}

template<class T>
bool List<T>::Empty()
{
	return _head->_next == _head;
}

void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.PushFront(0);
	l.PopFront();
	l.Print();

	List<string> l1;
	l1.PushBack("11");
	l1.PushBack("22");
	l1.PushBack("33");
	l1.PushBack("44");
	l1.PushBack("55");
	l1.Print();
}
