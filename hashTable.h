#pragma once
#include<map>
#include<vector>
/* 除留余数法选择的除数（平衡因子），选择成质数可以减少冲突，因为质数的约数只有1和它本身，
但是合数的约数肯定比1和它本身多，导致顺序表里面的下标被重复命中的次数增加，质数会降低哈希冲突*/
using namespace std;

#define MAX_HASH 11
namespace lxh
{
	class dealint
	{
	public:
		int operator()(int n)
		{
			return n;
		}

		/*int operator()(const string &s)
		{
			int sum = 0;
			int seed = 131;
			for (const char & c : s)
			{
				sum = sum * seed + c;
			}
			return sum & 0x7FFFFFFF;
		}*/

	};

	class dealstr
	{
	public:
		int operator()(const string &s)
		{
			int sum = 0;
			int seed = 131;
			for (const char & c:s)
			{
				sum = sum * seed + c;
			}
			return sum & 0x7FFFFFFF;
		}
	};
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};
	template<class K, class V,class SW = dealint>
	class hashTable
	{
		struct elem
		{

			State m_state;
			std::pair<K, V> m_val;
			elem(const K & key = K(), const V & val = V(), State tmp = EMPTY)
				:m_val(key, val),
				m_state(tmp)
			{}
		};

		vector<elem> m_table;
		size_t m_size;
		static long long s_m_primeTable[30];
		int m_primePos = 0;

	public:
		hashTable(size_t _capacity = MAX_HASH) :m_size(0)
		{
			m_table.resize(_capacity);
		}

		size_t hash_capacity()
		{
			return m_table.size();
		}
	private:
		int hashFunc(const K &key)
		{
			SW func;
			return func(key) % hash_capacity();
		}

	public:
		bool insert(const pair<K, V>&val)
		{
			if ((long long)m_size*100 / capacity()>=75)
			{
				//扩容
				reserve();
			}
			int n = hashFunc(val.first);
			//EMPTY和DELETE可以插入,线性探测
			while (m_table[n].m_state == EXIST)
			{
				if (m_table[n].m_val.first == val.first)
				{
					return false;
				}
				n++;
				if (n == hash_capacity())
				{
					n = 0;
				}
			}
			m_table[n].m_val = val;
			m_table[n].m_state = EXIST;
			m_size++;
			return true;
		}
		int find(const K & key)
		{
			int n = hashFunc(key);
			while (m_table[n].m_state != EMPTY)
			{
				if (m_table[n].m_state == EXIST && m_table[n].m_val == key)
				{

					return n;

				}
				n++;
				if (n >= hash_capacity())
				{
					n = 0;
				}
			}
			return -1;
		}
		bool reserve()
		{
			//此处所开辟的空间大小是，查质数表所得
			vector<elem> tmp;
			m_table.swap(tmp);

			m_table.resize(s_m_primeTable[++m_primePos]);

			//开辟新的空间之后将原来的表里面的数据，移动到新表里面，因为表的容量变大了，
			//哈希函数的映射关系会发生变化。
			m_size = 0;
			for (auto & e : tmp)
			{
			
				if (e.m_state==EXIST)
				{
					insert(e.m_val);
				}
			}

		}
		bool erase(K & key)
		{
			int ret = find(key);
			if (ret < 0)
			{
				return false;
			}
			else
			{
				m_table[ret].m_state = DELETE;
				m_size--;
			}

		}
		size_t size()
		{
			return m_size;
		}
		bool empty()
		{
			return m_size == 0;
		}
		void Swap(hashTable<K, V>& ht)
		{
			m_table.swap(ht.m_table);
			size_t tmp = m_size;
			m_size = ht.m_size;
			ht.m_size = tmp;
		}
		
	};
	template<class K, class V, class SW>
	long long hashTable<K, V, SW>::s_m_primeTable[30] =
	{
			11,         23,         47,         89,        179,
		   353,        709,       1409,       2819,       5639,
		 11273,      22531,      45061,      90121,     180233,
		360457,     720899,    1441807,    2883593,    5767169,
	  11534351,   23068673,   46137359,   92274737,  184549429,
	 369098771,  738197549, 1476395029, 2952790016u, 4294967291u

	};
}
