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
	T& Back()
	{
		return *(_finish - 1);
	}
	T& Front()
	{
		return *_first;
	}
	~Vector()
	{
		delete[] _first;
		_first = _finish = _endofstorge = NULL;
	}
	void Expand(size_t n)
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
			//memcpy(tmp, _first, Size() * sizeof(T));//当为string类型时，牵扯到深浅拷贝问题，摒弃memcpy这种做法
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
	void PushBack(const T& data)
	{
		Insert(Size(), data);
	}
	void PopBack()
	{
		Erase(Size() - 1);
	}
	void Insert(size_t pos, const T& data);
	void Erase(size_t pos)
	{
		assert(pos < Size());
		T* start = _first + pos + 1;
		while (start < _finish)
		{
			*(start-1) = *(start);
			++start;
		}
		--_finish;
	}
	size_t Find(const T& data)
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
	const T&operator[](size_t pos) const
	{
		return _first[pos];
	}
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
