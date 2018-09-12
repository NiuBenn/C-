#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

// 1.现代写法 
// 2.传统写法 
// 3.字符串增删查改 

class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])	//开str长度+1个空间，末尾有\0
	{
		strcpy(_str, str);
		_size = strlen(str);
		_capacity = _size;
	}
	// s1.Swap(s2); 
	void Swap(String& s)
	{
		swap(this->_str, s._str);
		swap(this->_size, s._size);
		swap(this->_capacity, s._capacity);
	}

	// String s2(s1) 
	String(const String& s)
		:_str(NULL)
	{
		String tmp(s._str);
		swap(_str, tmp._str);
		_size = tmp._size;
		_capacity = tmp._capacity;
	}
	// s1 = s2 
	String& operator=(String s)
	{
		if (this != &s)
		{
			String tmp(s._str);
			swap(_str, s._str);
		}
		return *this;
	}

	~String()
	{
		delete[] _str;
		_str = NULL;
	}
	
	const char* c_str()
	{
		return _str;
	}

	void Expand(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}

	char& operator[](size_t pos)
	{
		assert(pos < _size);

		return _str[pos];
	}

	void PushBack(char ch)
	{
		if (_capacity == _size)
		{
			Expand(_capacity * 2);
		}
		_str[_size] = ch;
		_size++;
		_str[_size] = '\0';
	}

	void PushBack(const char* str)
	{
		size_t len = strlen(str);
		if (_capacity < _size + len)
		{
			Expand(_size + len);
		}
		strcpy(_str + _size, str);
		_size += len;
	}

	void PopBack()
	{
		_str[_size] = '\0';
	}

	void Insert(size_t pos, char ch)
	{
		assert(pos < _size);
		if (_size == _capacity)
		{
			Expand(_capacity * 2);
		}

		int end = _size;

		while (end >= (int)pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}

		_str[pos] = ch;
		++_size;
	}

	void Insert(size_t pos, const char* str)
	{
		assert(pos < _size);
		
		size_t len = strlen(str);
		if (_capacity < _size + len)
		{
			Expand(_size + len);
		}

		int end = _size;
		while (end >= (int)pos)
		{
			_str[end + len] = _str[end];
			end--;
		}

		for (size_t i = 0; i < len; ++i)
		{
			_str[pos + i] = str[i];
		}
		_size += len;
	}

	void Erase(size_t pos, size_t len = 1)
	{
		assert(pos < _size);
		if (pos + len > _size)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			int cur = pos + len;
			for (size_t i = 0; i < _size - cur; ++i)
			{
				_str[pos + i] = _str[cur + i];
			}

			_size -= len;
		}

	}


	size_t Find(char ch)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return -1;
	}
	size_t Find(const char* str) // ? 
	{
		assert(str);
		size_t strindex = 0;
		size_t srcindex = 0;
		//size_t len = strlen(sub);

		while (srcindex < _size)
		{
			size_t matchindx = srcindex;
			while (str[strindex] != '\0'
				&& _str[matchindx] == str[strindex])
			{
				++matchindx;
				++strindex;
			}

			if (str[strindex] == '\0')
			{
				return srcindex;
			}
			else
			{
				++srcindex;
				strindex = 0;
			}
		}

		return -1;
	}

	// s1 + 'a' 
	String operator+(char ch)
	{
		String tmp(this->_str);
		tmp.PushBack(ch);
		return tmp;
	}

	String& operator+=(char ch)
	{
		this->PushBack(ch);
		return *this;
	}

	String operator+(const char* str)
	{
		String tmp(this->_str);
		tmp.PushBack(str);
		return tmp;
	}

	String& operator+=(const char* str)
	{
		this->PushBack(str);
		return *this;
	}

	bool operator==(const String& s) const
	{
		const char* str1 = _str;
		const char* str2 = s._str;

		while (*str1 && *str2)
		{
			if (*str1 != *str2)
			{
				return false;
			}
			else
			{
				++str1;
				++str2;
			}
		}

		if (*str1 == '\0' && *str2 == '\0')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(const String&s) const
	{
		const char* str1 = _str;
		const char* str2 = s._str;

		while (*str1 && *str2)
		{
			if (*str1 > *str2)
			{
				return false;
			}
			else if (*str1 < *str2)
			{
				return true;
			}
			else
			{
				++str1;
				++str2;
			}
		}

		if (*str1 == '\0' && *str2 == '\0')
		{
			return false;
		}
	}

	bool operator<=(const String& s) const
	{
		return *this < s || *this == s;
	}

	bool operator>(const String& s) const
	{
		return !(*this <= s);
	}

	bool operator>=(const String& s) const
	{
		return !(*this < s);
	}

	bool operator!=(const String& s) const
	{
		return !(*this == s);
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

int main()
{
	String s1("change world");
	String s2(s1);
	s2.PushBack('!');


	s2.PushBack("I am Coming");

	s1 += "I am Coming";

	s1 += '!';;

	system("pause");
	return 0;

}
