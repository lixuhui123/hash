#pragma once
#include<vector>
#include<string>
using namespace std;
#define MAX_HASH 11
template<class T>
class hashBucketNode
{
	T val;
	hashBucketNode<T> * m_next;//ָ�������ͬ���͵Ľڵ㣬��ΪͰ��ͷ��

	hashBucketNode(const T & _val = T()) :
		val(_val), m_next(nullptr)
	{}


	template<class T, class SW>
	friend class hashSet
};


class dealint
{
public:
	int operator()(int n)
	{
		return n;
	}

	int operator()(const string &s)
	{
		int sum = 0;
		int seed = 131;
		for (const char & c : s)
		{
			sum = sum * seed + c;
		}
		return sum & 0x7fffffff;
	}

};
template<class T, class SW = dealint>
class hashSet
{

	vector<hashBucketNode<T> *> m_data;
	size_t m_size;//Ԫ�ظ�����Ͱ�ĸ�����



public:
	hashSet(size_t _capacity = MAX_HASH):m_size(0)
	{
		m_data.resize(_capacity);
	}

	int hash_capacity()
	{
		return m_data.size();
	}

	int hashFunc(const T &key)
	{
		SW func;
		return func(key) % hash_capacity();//�ҵ�Ͱ���±�
	}

	/*hashBucketNode<T> * find(const T & key)
	{
		int ret = hashFunc(key);
		return m_data[ret];
	}*/

	bool insert(const T & key)
	{
		int ret = hashFunc(key);//�õ���Ӧ��Ͱ��λ��
		hashBucketNode<T> * tmp = new hashBucketNode<T>(key);

		tmp->m_next = m_data[ret];
		m_data[ret] = tmp;

		m_size++;

		return true;
	}

	bool erase(const T & key)
	{
		int ret = hashFunc(key);
		hashBucketNode<T> * tmp = m_data[ret];//�ҵ��˶�Ӧ��Ͱ����

		if (!tmp)//Ͱ�ǿյ�
		{
			return false;
		}
		else
		{
			//Ͱ��Ϊ�գ������������1��Ͱ����û�����Ԫ�أ�2��Ͱ������ɾ��
			
			
			if (tmp->val==key)
			{
				//��ͷ
				hashBucketNode<T> * cur;
				cur = tmp;
				m_data[ret] = cur->m_next;
				delete cur;
				m_size--;
				return true;
			}
			else
			{
				/* ����������� */
				for (cur = tmp; cur->m_next; cur = cur->m_next)
				{

					if (cur->m_next->val == key)
					{
						//�ҵ�Ҫɾ����Ԫ����
						hashBucketNode<T> * del=cur->m_next;
						cur->m_next = del->m_next;
						delete del;
						m_size--;
						return true;
					}
				}
			}
			return false;

		}

	}
};