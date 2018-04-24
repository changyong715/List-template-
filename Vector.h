#include<iostream>
#include<assert.h>
using namespace std;

typedef int DataType;

class Vector
{
public:
	Vector()
		:_first(NULL)
		,_finish(NULL)
		,_endofstorage(NULL)
	{}
	~Vector()
	{
		delete[] _first;
		_first = _finish = _endofstorage = NULL;
	}
	size_t Size()
	{
		return _finish - _first;
	}
	size_t Capacity()
	{
		return _endofstorage - _first;
	}
	void Expand(size_t n);
	void PushBack(DataType x);
	void Show();
	void PopBack();
	void Insert(size_t pos, DataType x);
	void Erase(size_t pos);
	size_t Find(DataType x);
private:
	DataType *_first;//顺序表头
	DataType *_finish;//元素末尾指针
	DataType *_endofstorage;//容量指针
};
void Vector::Show()
{
	DataType* cur = _first;
	while (cur != _finish)
	{
		printf("%d ", *cur);
		cur++;
	}
	printf("\n");
}
void Vector::Expand(size_t n)
{
	if (n > Capacity())
	{
		size_t size = Size();
		DataType* tmp = new DataType[n];
		if (_first)
		{
			memcpy(tmp, _first, sizeof(DataType)*Size());
			delete[]_first;
		}
		_first = tmp;
		_finish = _first + size;
		_endofstorage = _first + n;
	}
}
void Vector::PushBack(DataType x)
{
	/*if (_endofstorage == _finish)//扩容
  {
	    if (Capacity() == 0)
	  {
    	Expand(5);
  	}
	    else
   	{
    	Expand(Capacity() * 2);
  	}
	}
	*_finish = x;
	_finish++;*/
	Insert(Size(), x);
}
void Vector::PopBack()
{
	assert(_finish > _first);
	//_finish--;
	Erase(Size());
}
void Vector::Insert(size_t pos,DataType x)
{
	if (_finish == _endofstorage)
	{
		if (Capacity() == 0)
			Expand(3);
		else
			Expand(Capacity() * 2);
	}
	int end = Size() - 1;
	while (end >= (int)pos)
	{
		_first[end + 1] = _first[end];
		end--;
	}
	_first[pos] = x;
	_finish++;
}
void Vector::Erase(size_t pos)
{
	assert(_finish > _first);
	size_t begin = pos;
	while (begin <= Size())
	{
		_first[begin] = _first[begin + 1];
		begin++;
	}
	_finish--;
}
size_t Vector::Find(DataType x)
{
	DataType* cur = _first;
	while (cur != _finish)
	{
		if (*cur == x)
			return *cur;
		cur++;
	}
	return -1;
}
void Test2()
{
	Vector v;
	v.PushBack(0);
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	v.PushBack(6);
	v.PushBack(7);
	v.Show();
}
