#pragma once
#include <map>
#include <vector>
using namespace std;
enum state
{
	EMPTY,
	EXIST,
	DELETE
};
class dealint
{
public:
	int operator()(int tmp)
	{
		return tmp;
	}
};

class dealstr
{
	int operator()(const string &str)
	{
		int sum = 0;
		int seed = 131;
		for (auto & e:str)
		{
			sum = sum * seed + e;
		}
		return sum & 0x7FFFFFFF;
	}
};
namespace lxh
{
	template<class K, class V, class FUNC = dealint>
	class hashTable
	{
		struct elem
		{
			state m_state;
			std::pair<K, V> m_val;
			elem(const K & k = K(),const V & v=V(),state st=EMPTY)
				:m_val.first(k),m_val.second(v),m_state(EMPTY)
			{}
		};
		vector<elem> m_table;
		int m_size = 0;
		static long long s_m_primearr[30];
		int m_prime_pos = 0;
		int m_capicaty = s_m_primearr[m_prime_pos];
		void hash_size()
		{
			return m_size;
		}
		void reserve()
		{
			vector<elem> tmp;
			m_table.swap(tmp);
			m_table.resize(s_m_primearr[++m_prime_pos],elem);
			m_size = 0;
			for (auto & e : tmp)
			{
				if (e.m_state==EXIST)
				{
					m_table.insert(e.m_val);
				}
			}

		}

		bool insert(const pair<K, V>& tmp)
		{
			if (m_size*100/m_capicaty>=75)
			{
				reserve();
			}
			int n = hashFunc(tmp.first);
			while (m_table[n].m_state == EXIST)
			{
				if (m_table[n].m_val.first==tmp.first)
				{
					return false;
				}
				++n;
				if (n==m_capicaty)
				{
					n = 0;
				}
			}

			m_table[n].m_state = EXIST;
			m_table[n].m_val = tmp;
			m_size++;
			return true;
		}

		bool erase(K & key)
		{
			int n = find(key);
			if (n == -1)
			{
				return false;
			}
			else
			{
				m_table[n].m_state = DELETE;
				m_size--;
			}
		}
		int find(const K & key)
		{
			 
			int hashret = hashFunc(key);

			while (m_table[hashret].m_state != EMPTY)
			{
				if (m_table[hashret].m_state==EXIST && m_table[hashret].m_val==key)
				{
					return hashret;
				}
				++hashret;
				if (n == m_capicaty)
				{
					hashret = 0;
				}
			}
			return -1;

		}

		int hashFunc(const K & key)
		{
			FUNC func;
			return func(key) % m_capicaty;

		}
		bool empty()
		{
			return 0 == hash_size();
		}
		bool swap(hashTable<K,V> &tmp)
		{

			m_table.swap(tmp.m_table);
			int t_size = m_size;
			m_size = tmp.m_size;
			tmp.m_size = t_size;
		}
	};
	template<class K,class V,class FUNC>
	long long hashTable<K,V, FUNC>::s_m_primearr[30]=
	{
		11,         23,         47,         89,        179,
	   353,        709,       1409,       2819,       5639,
	 11273,      22531,      45061,      90121,     180233,
	360457,     720899,    1441807,    2883593,    5767169,
  11534351,   23068673,   46137359,   92274737,  184549429,
 369098771,  738197549, 1476395029, 2952790016u, 4294967291u

	};
}

