#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include <string.h>
namespace tao
{
	class string
	{
 	  public:
		  typedef char* iterator;//��ͨ������
		  typedef  const char* const_iterator; //const������

		  //�޲ι���---������û�����ݣ�����һ��\0�ģ���û�д�С,��Ϊ\0�������С������
		 /* string()
		  {
			  _size = _capacity = 0;
			  _str = new char[1];
			  _str[0] = '\0';
		  }*/
		  string(const char* str="")//�������޲ι���һ���á�ȫȱʡ//�����ַ�������Ĭ����\0
		  {
			  _size = strlen(str);
			  _capacity = _size;
			  //_str=str
			  //����ֱ�ӽ�str����_str����Ϊstr��const���εģ�����涨�ģ������Ա��޸ģ���_str����const���͵�
			  //����Ҫ����һ���strһ����Ŀռ䣬Ȼ�󿽱���_str
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
		  //Ҫʵ�ֱ��������������С
		 size_t size() const //һ��ֻ���������޸�
		 {
			 return _size;
		 }
		 char& operator[](int pos)//�������÷��أ���Ϊ���˺���ֵ����
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //�������������ͣ�һ�����������һ����const���εĶ���ֻ���������޸ĵ�
		 const char& operator[](int pos) const
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //ͨ�����������б�������������һ�����ͣ���string�����һ�����ͣ��������ڲ��࣬Ҳ�������Զ���ġ�
		 //�����������Զ���һ��iterator��
		 iterator begin()//begin���ص���ָ��ͷλ�õĵ�����
		 {
			 return _str;
		 }
		 iterator end()//end���ص���ָ�����һ���ַ�����һ��λ��
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
		 //��ɾ���
		 void push_back(char ch)//β�����㰴��Ҫ�����Ƿ���Ҫ����--->���������reserve������
		 {
			 if (_size >= _capacity)
			 {
				 //����ֱ������2������Ҫע��һ���������Ϊ�մ�ʱ
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
				 //���������ֱ��2�����ݣ���Ϊ����2�����ݺ������������
				 //������Ҫ���ݵ�_size+len��С
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