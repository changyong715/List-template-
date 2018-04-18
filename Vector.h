#include<iostream>
using namespace std;

typedef int DataType;

struct ListNode
{
	ListNode* _next;//后继指针
	ListNode* _prev;//前驱指针
	DataType _data;

	ListNode(DataType x)//初始化
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};
class List
{
	typedef ListNode Node;//定义为私有的，只有类内可以访问，避免了命名冲突
public:
	List()
		:_head(new Node(DataType()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void Sign(const List& l)//赋值拷贝的函数
	{
		_head->_next = _head;
		_head->_prev = _head;
		Node* cur = l._head->_next;
		Node* Newcur = _head->_next;
		Node* tmp = NULL;
		while (cur != l._head)//逐一拷贝
		{
			if (Newcur->_next == _head)//头节点操作
			{
				tmp = new Node(DataType(cur->_data));
				Link(Newcur, tmp);
			}
			else//非头结点操作
			{
				while (Newcur->_next != _head)//找到要链接的位置
					Newcur = Newcur->_next;
				tmp = new Node(DataType(cur->_data));
				Link(Newcur, tmp);//进行链接
			}
			cur = cur->_next;
		}
	}
	List(const List& l)//拷贝构造函数
		:_head(new Node(DataType()))
	{
		Sign(l);
	}
	~List()
	{
		cout << "~List()" << endl;
		clean();
	}
	void clean()//收尾，对动态申请的节点的释放
	{
		Node* cur = _head->_next;
		Node* tmp = NULL;
		while (cur != _head)
		{
			tmp = cur->_next;
			delete cur;
			cur = tmp;
		}
		cur = NULL;
	}
	List& operator=(const List& l)
	{
		if (_head != l._head)//避免自己给自己赋值
		{
			clean();//清除原有的链表结构
			Sign(l);
		}
		return *this;
	}
	void Link(Node* cur,Node* tmp)//将两个节点链接起来(双向链表的链接)
	{
		tmp->_prev = cur;
		tmp->_next = cur->_next;
		cur->_next->_prev = tmp;
		cur->_next = tmp;
	}
	void PushBack(DataType x)
	{
		Node* cur = _head->_next;
		while (cur->_next != _head)//找尾
			cur = cur->_next;
		//Node* tmp = new Node(DataType(x));//方法1
		//Link(cur, tmp);
		Insert(cur, x);//方法2
	}
	void show()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			printf("%d ", cur->_data);
			cur = cur->_next;	
		}
		printf("\n");
	}
	void PushFront(DataType x)
	{
		Node* tmp = new Node(DataType(x));
		//Link(_head, tmp);//方法1
		Insert(_head, x);//方法2
	}
	void PopBack()
	{
		if (_head->_next == _head)
			return;
		Node* cur = _head->_next;
		Node* parent = _head;
		while (cur->_next != _head)//找尾，并且记住其前驱，方便链接
		{
			parent = cur;
			cur = cur->_next;
		}
		//方法1
		/*parent->_next = cur->_next;
		cur->_next->_prev = parent;
		delete cur;
		cur = NULL;*/
		//方法2
		Erase(cur);
	}
	void PopFront()
	{
		if (_head->_next == _head)
			return;
		//方法1
		/*Node* cur = _head->_next;
		_head->_next = cur->_next;
		cur->_next->_prev = _head;
		delete cur;
		cur = NULL;*/
		//方法2
		Erase(_head->_next);
	}
	Node* Find(DataType x)
	{
		if (_head->_next == _head)
			return NULL;
		Node* cur = _head->_next;
		while (cur != _head)
		{
			if (cur->_data == x)
				return cur;
			cur = cur->_next;
		}
		return NULL;
	}
	void Insert(Node* pos, DataType x)
	{
		Node* node = new Node(DataType(x));
		if (pos == _head)//处理头结点
		{
			Link(_head, node);
		}
		else//非头结点
		{
			Node* cur = _head->_next;
			while (cur != _head)
			{
				if (cur == pos)
				{
					Link(cur, node);
					return;
				}
				cur = cur->_next;
			}
		}
	}
	void Erase(Node* pos)
	{
		if (pos == _head)
			return;
		Node* cur = _head->_next;
		Node* parent = _head;
		while (cur != _head)
		{
			if (cur == pos)
			{
				cur->_next->_prev = parent;
				parent->_next = cur->_next;
				delete cur;
				cur = NULL;
				return;
			}
			parent = cur;
			cur = cur->_next;
		}
	}
private:
	Node * _head;
};

void Test1()
{
	List l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	printf("尾插>");
	l.show();
	l.PushFront(0);
	printf("头插>");
	l.show();
	printf("尾删>");
	l.PopBack();
	l.show();
	printf("头删>");
	l.PopFront();
	l.show();
	cout << "查找4: "<<l.Find(4)<<"->"<<l.Find(4)->_data << endl;
	printf("L拷贝构造>");
	List L(l);
	L.show();
	L.PushBack(99);
	printf("L尾插99>");
	L.show();
	l = L;
	printf("赋值，将L赋给l>");
	l.show();
}
