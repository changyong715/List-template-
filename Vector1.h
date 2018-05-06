#pragma once
#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

//类名 Vector
//类型 Vector<T>
template<class T>
class Vector {
public:
	Vector()
		:_first(NULL)
		, _finish(NULL)
		, _endofstorge(NULL)
	{}
	~Vector()
	{
		delete[] _first;
		_first = _finish = _endofstorge = NULL;
	}
	Vector(const Vector<T>& t)//Vector<T>才是类型，和以前注意区分
	{
		if (t._finish!=t._first)
		{
			size_t size = t._finish - t._first;
			_first = new T[size];//给新对象分配空间
			memcpy(_first, t._first, sizeof(T)*size);//拷贝数据
			_finish = _first + size;
			_endofstorge = _first + size;
		}
		else
			_first = _finish = _endofstorge = NULL;
	}
	T& Back()
	{
		return *(_finish - 1);
	}
	T& Front()
	{
		return *_first;
	}
	void Expand(size_t n);
	void PushBack(const T& data);
	void PopBack();
	void Insert(size_t pos, const T& data);
	void Erase(size_t pos);
	size_t Find(const T& data);
	const T&operator[](size_t pos) const;
	size_t Size()
	{
		return _finish - _first;
	}
	size_t Capacity()
	{
		return _endofstorge - _first;
	}
	bool Empty()
	{
		return _first == _finish;
	}
protected:
	T* _first;
	T* _finish;
	T* _endofstorge;
};

template<class T>
void Vector<T>::Expand(size_t n)
{
	if (Empty())
	{
		_first = _finish = new T[3];
		_endofstorge = _finish + 3;
	}
	else
	{
		size_t size = Size();
		T* tmp = new T[n];
		//memcpy(tmp, _first, Size() * sizeof(T));
		for (size_t i = 0; i < size; i++)
		{
			tmp[i] = _first[i];
		}
		delete[] _first;
		_first = tmp;
		_finish = _first + size;
		_endofstorge = _first + n;
	}
}

template<class T>
void Vector<T>::Insert(size_t pos, const T& data)
{
	if (Capacity() >= Size())
	{
		Expand(Capacity() * 2);
	}
	T* end = _finish-1;
	while (end >= pos + _first)
	{
		*(end + 1) = *end;
		--end;
	}
	*(_first + pos) = data;
	++_finish;
}

template<class T>
void Vector<T>::PushBack(const T& data)
{
	Insert(Size(), data);
}

template<class T>
void Vector<T>::PopBack()
{
	Erase(Size() - 1);
}

template<class T>
void Vector<T>::Erase(size_t pos)
{
	assert(pos < Size());
	T* start = _first + pos + 1;
	while (start < _finish)
	{
		*(start - 1) = *(start);
		++start;
	}
	--_finish;
}

template<class T>
size_t Vector<T>::Find(const T& data)
{
	T* start = _first;
	while (start != _finish)
	{
		if (*start == data)
		{
			return start - _first;
		}
		++start;
	}
	return -1;
}

template<class T>
const T& Vector<T>::operator[](size_t pos)const
{
	return _first[pos];
}
void TestVector()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	for (size_t i = 0; i < v1.Size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	
	Vector<char> v2;
	v2.PushBack('a');
	v2.PushBack('b');
	v2.PushBack('c');
	v2.PushBack('d');
	for (size_t i = 0; i < v2.Size(); i++)
	{
		cout << v2[i] << " ";
	}
	cout << endl;

	Vector<string> v3;
	v3.PushBack("11");
	v3.PushBack("22");
	v3.PushBack("33");
	v3.PushBack("44");
	for (size_t i = 0; i < v3.Size(); i++)
	{
		cout << v3[i] << " ";
	}
	cout << endl;
}
