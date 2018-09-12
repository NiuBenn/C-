#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>

using namespace std;
typedef int DataType;

struct ListNode
{
	ListNode* _next;
	ListNode* _prev;
	DataType _data;

	ListNode(DataType x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};

class List
{
	typedef ListNode Node;
public:
	List()
		:_head(new Node(DataType()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	List(const List& l)
	{
		_head = new Node(DataType());
		_head->_next = _head;
		_head->_prev = _head;

		Node* cur = l._head->_next;
		while (cur != l._head)
		{
			this->PushBack(cur->_data);
			cur = cur->_next;
		}
	}

	List& operator=( List l)
	{
		swap(_head, l._head);
		return *this;
	}

	~List()
	{
		Node* cur = _head->_next;

		while (cur != _head)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}

		delete _head;
		_head = NULL;
	}

	void PushBack(DataType x)
	{
		Insert(_head, x);
	}

	void PushFront(DataType x)
	{
		Insert(_head->_next, x);
	}

	void PopBack()
	{
		Erase(_head->_prev);
	}
	void PopFront()
	{
		Erase(_head->_next);
	}

	Node* Find(DataType x)
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			if (cur->_data == x)
			{
				return cur;
			}
			cur = cur->_next;
		}

		return NULL;
	}

	void Insert(Node* pos, DataType x)
	{
		Node* prev = pos->_prev;
		Node* newnode = new Node(x);
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = pos;
		pos->_prev = newnode;
	}
	void Erase(Node* pos)
	{
		Node* prev = pos->_prev;
		Node* next = pos->_next;
		delete pos;
		prev->_next = next;
		next->_prev = prev;
	}

	void Print()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}

private:
	Node * _head;
};

int main()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);

	l1.Print();

	List l2(l1);
	l2.Print();

	List l3;
	l3.PushBack(10);
	l3.PushBack(20);
	l3.PushBack(30);

	l2 = l3;
	l2.Print();

	system("pause");
	return 0;


}
