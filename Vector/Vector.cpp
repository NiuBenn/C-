#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdlib.h>
#include<assert.h>

using namespace std;
typedef int DataType;

class Vector
{
public:
	Vector()
		:_first(NULL),_finish(NULL),_endofstorage(NULL)
	{
	}

	Vector(const Vector& v)
	{
		_first = new DataType[v.Size()];
		_finish = _first + v.Size();
		_endofstorage = _first + v.Size();

		memcpy(_first, v._first, sizeof(DataType)*v.Size());
	}

	Vector& operator=( Vector v)
	{
		swap(_first, v._first);
		swap(_finish, v._finish);
		swap(_endofstorage, v._endofstorage);

		return *this;
	}
	~Vector()
	{
		delete[] _first;
		_first = NULL;
		_finish = NULL;
		_endofstorage = NULL;
	}
	size_t Size() const
	{
		return _finish - _first;
	}
	size_t Capacity() const
	{
		return _endofstorage - _first;
	}

	void Expand(size_t n)
	{
		if (n > Capacity())
		{
			size_t size = Size();
			DataType* tmp = new DataType[n];
			memcpy(tmp, _first, size * sizeof(DataType));

			delete[] _first;
			_first = tmp;
			_finish = _first + size;
			_endofstorage = _first + n;
		}
	}
	void PushBack(DataType x)
	{
		if (_finish == _endofstorage)
		{
			size_t newcapacity = Capacity() > 0 ? Capacity()*2 : 3;
			Expand(newcapacity);
		}

		*_finish = x;
		++_finish;
	}	

	void Reserve(size_t n, DataType value)
	{
		if (n < Size())
		{
			_finish = _finish + n;
		}
		else
		{
			if (n > Capacity())
			{
				Expand(n);
			}
			DataType* end = _first + n;
			while (_finish < end)
			{
				*_finish = value;
				++_finish;
			}
		}
	}
	void PopBack()
	{
		assert(_finish > _first);
		--_finish;
	}
	void Insert(size_t pos, DataType x)
	{
		assert(pos < Size() - 1);
		if (Size() == Capacity())
		{
			Expand(Size() * 2);
		}

		size_t end = Size();
		for(size_t i = end; i > pos; ++i)
		{
			(*this)[i] = (*this)[i - 1];
		}

		(*this)[pos] = x;
		_finish++;
	}
	void Erase(size_t pos)
	{
		assert(pos < Size() - 1);
		size_t end = Size();

		for (size_t i = pos; i < end - 1; ++i)
		{
			(*this)[i] = (*this)[i + 1];
		}

		--_finish;
	}
	size_t Find(DataType x)
	{
		size_t end = Size();
		for (size_t i = 0; i < end; ++i)
		{
			if ((*this)[i] == x)
			{
				return i;
			}
		}
		return -1;
	}

	DataType& operator[](size_t pos)
	{
		return _first[pos];
	}


private:
	DataType * _first;
	DataType* _finish;
	DataType* _endofstorage;
};


int main()
{

	Vector v1;
	//v1.Reverse(10);
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	v1.PushBack(6);
	v1.PushBack(7);

	for (size_t i = 0; i < v1.Size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}