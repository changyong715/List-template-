#include<iostream>
using namespace std;

typedef int DataType;

struct ListNode
{
	ListNode* _next;//���ָ��
	ListNode* _prev;//ǰ��ָ��
	DataType _data;

	ListNode(DataType x)//��ʼ��
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};
class List
{
	typedef ListNode Node;//����Ϊ˽�еģ�ֻ�����ڿ��Է��ʣ�������������ͻ
public:
	List()
		:_head(new Node(DataType()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void Sign(const List& l)//��ֵ�����ĺ���
	{
		_head->_next = _head;
		_head->_prev = _head;
		Node* cur = l._head->_next;
		Node* Newcur = _head->_next;
		Node* tmp = NULL;
		while (cur != l._head)//��һ����
		{
			if (Newcur->_next == _head)//ͷ�ڵ����
			{
				tmp = new Node(DataType(cur->_data));
				Link(Newcur, tmp);
			}
			else//��ͷ������
			{
				while (Newcur->_next != _head)//�ҵ�Ҫ���ӵ�λ��
					Newcur = Newcur->_next;
				tmp = new Node(DataType(cur->_data));
				Link(Newcur, tmp);//��������
			}
			cur = cur->_next;
		}
	}
	List(const List& l)//�������캯��
		:_head(new Node(DataType()))
	{
		Sign(l);
	}
	~List()
	{
		cout << "~List()" << endl;
		clean();
	}
	void clean()//��β���Զ�̬����Ľڵ���ͷ�
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
		if (_head != l._head)//�����Լ����Լ���ֵ
		{
			clean();//���ԭ�е�����ṹ
			Sign(l);
		}
		return *this;
	}
	void Link(Node* cur,Node* tmp)//�������ڵ���������(˫�����������)
	{
		tmp->_prev = cur;
		tmp->_next = cur->_next;
		cur->_next->_prev = tmp;
		cur->_next = tmp;
	}
	void PushBack(DataType x)
	{
		Node* cur = _head->_next;
		while (cur->_next != _head)//��β
			cur = cur->_next;
		//Node* tmp = new Node(DataType(x));//����1
		//Link(cur, tmp);
		Insert(cur, x);//����2
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
		//Link(_head, tmp);//����1
		Insert(_head, x);//����2
	}
	void PopBack()
	{
		if (_head->_next == _head)
			return;
		Node* cur = _head->_next;
		Node* parent = _head;
		while (cur->_next != _head)//��β�����Ҽ�ס��ǰ������������
		{
			parent = cur;
			cur = cur->_next;
		}
		//����1
		/*parent->_next = cur->_next;
		cur->_next->_prev = parent;
		delete cur;
		cur = NULL;*/
		//����2
		Erase(cur);
	}
	void PopFront()
	{
		if (_head->_next == _head)
			return;
		//����1
		/*Node* cur = _head->_next;
		_head->_next = cur->_next;
		cur->_next->_prev = _head;
		delete cur;
		cur = NULL;*/
		//����2
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
		if (pos == _head)//����ͷ���
		{
			Link(_head, node);
		}
		else//��ͷ���
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
	printf("β��>");
	l.show();
	l.PushFront(0);
	printf("ͷ��>");
	l.show();
	printf("βɾ>");
	l.PopBack();
	l.show();
	printf("ͷɾ>");
	l.PopFront();
	l.show();
	cout << "����4: "<<l.Find(4)<<"->"<<l.Find(4)->_data << endl;
	printf("L��������>");
	List L(l);
	L.show();
	L.PushBack(99);
	printf("Lβ��99>");
	L.show();
	l = L;
	printf("��ֵ����L����l>");
	l.show();
}
