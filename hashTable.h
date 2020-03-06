#pragma once
#include<map>
#include<vector>
/* ����������ѡ��ĳ�����ƽ�����ӣ���ѡ����������Լ��ٳ�ͻ����Ϊ������Լ��ֻ��1��������
���Ǻ�����Լ���϶���1��������࣬����˳���������±걻�ظ����еĴ������ӣ������ή�͹�ϣ��ͻ*/
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
				//����
				reserve();
			}
			int n = hashFunc(val.first);
			//EMPTY��DELETE���Բ���,����̽��
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
			//�˴������ٵĿռ��С�ǣ�������������
			vector<elem> tmp;
			m_table.swap(tmp);

			m_table.resize(s_m_primeTable[++m_primePos]);

			//�����µĿռ�֮��ԭ���ı���������ݣ��ƶ����±����棬��Ϊ�����������ˣ�
			//��ϣ������ӳ���ϵ�ᷢ���仯��
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
