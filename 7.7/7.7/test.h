#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include <string.h>
namespace tao
{
	class string
	{
 	  public:
		  typedef char* iterator;//普通迭代器
		  typedef  const char* const_iterator; //const迭代器

		  //无参构造---不代表没有数据，是有一个\0的，但没有大小,因为\0不计入大小计算中
		 /* string()
		  {
			  _size = _capacity = 0;
			  _str = new char[1];
			  _str[0] = '\0';
		  }*/
		  string(const char* str="")//可以与无参构造一起复用。全缺省//常量字符串后面默认有\0
		  {
			  _size = strlen(str);
			  _capacity = _size;
			  //_str=str
			  //不能直接将str赋给_str，因为str是const修饰的，库里规定的，不可以被修改，而_str不是const类型的
			  //而需要开辟一块跟str一样大的空间，然后拷贝给_str
			  _str = new char[_capacity + 1];
			  strcpy(_str, str);
	       }
		  ~string()
		  {
			  delete[] _str;
			  _str = nullptr;
			  _size = _capacity = 0;
		  }
		 const char* c_str() const
	      {
			  return _str;
		  }
		  //要实现遍历，首先需向大小
		 size_t size() const //一般只读，不给修改
		 {
			 return _size;
		 }
		 char& operator[](int pos)//可以引用返回，因为出了函数值还在
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //有两种重载类型，一种是上面的另一种是const修饰的对象，只读，不给修改的
		 const char& operator[](int pos) const
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //通过迭代器进行遍历，迭代器是一种类型，是string类里的一种类型，可以是内部类，也可以是自定义的。
		 //我们在这里自定义一个iterator。
		 iterator begin()//begin返回的是指向开头位置的迭代器
		 {
			 return _str;
		 }
		 iterator end()//end返回的是指向最后一个字符的下一个位置
		 {
			 return _str + _size;
		 }
		 iterator begin()const
		 {
			 return _str;
		 }
		 iterator end()const
		 {
			 return _str + _size;
		 }

		 void reserve(size_t n)
		 {
			 if (n > _capacity)
			 {
				 char* temp = new char[n + 1];
				 strcpy(temp, _str);
				 delete[] _str;
				_str = temp;
				_capacity = n;
			 }
		 }
		 //增删查改
		 void push_back(char ch)//尾插首秀按需要考虑是否需要扩容--->扩容最好用reserve来扩容
		 {
			 if (_size >= _capacity)
			 {
				 //可以直接扩容2倍，但要注意一种情况，当为空串时
				 reserve(_capacity == 0 ? 4 : 2 * _capacity);
				 _str[_size++] = ch;
				 _str[_size] = '\0';
			 }
		 }
		 void append(const char * str)
		 {
			 int len = strlen(str);
			 if (_size + len > _capacity)
			 {
				 //这个不可以直接2倍扩容，因为可能2倍扩容后的容量还不够
				 //至少需要扩容到_size+len大小
				 reserve(_size + len);
				 strcpy(_str + _size, str);
				 _size += len;
			 }
		 }
	  private:
		  char* _str;
		  int _size;
		  int _capacity;
	};




}