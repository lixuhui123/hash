#pragma once
#include<vector>
#include<string>
using namespace std;
#define MAX_HASH 11
template<class T>
class hashBucketNode
{
	T val;
	hashBucketNode<T> * m_next;//指向和它相同类型的节点，作为桶的头部

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
	size_t m_size;//元素个数（桶的个数）



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
		return func(key) % hash_capacity();//找到桶的下标
	}

	/*hashBucketNode<T> * find(const T & key)
	{
		int ret = hashFunc(key);
		return m_data[ret];
	}*/

	bool insert(const T & key)
	{
		int ret = hashFunc(key);//得到对应的桶的位置
		hashBucketNode<T> * tmp = new hashBucketNode<T>(key);

		tmp->m_next = m_data[ret];
		m_data[ret] = tmp;

		m_size++;

		return true;
	}

	bool erase(const T & key)
	{
		int ret = hashFunc(key);
		hashBucketNode<T> * tmp = m_data[ret];//找到了对应的桶在哪

		if (!tmp)//桶是空的
		{
			return false;
		}
		else
		{
			//桶不为空，有两种情况，1、桶里面没有这个元素，2、桶里有则删除
			
			
			if (tmp->val==key)
			{
				//砍头
				hashBucketNode<T> * cur;
				cur = tmp;
				m_data[ret] = cur->m_next;
				delete cur;
				m_size--;
				return true;
			}
			else
			{
				/* 首先链表遍历 */
				for (cur = tmp; cur->m_next; cur = cur->m_next)
				{

					if (cur->m_next->val == key)
					{
						//找到要删除的元素了
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