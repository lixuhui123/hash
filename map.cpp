#include <iostream>
#include<unordered_map>

using namespace std;
int mainedwe()
{
	unordered_map<int, int> um;//�����map����ɾ��Ч�ʸ��ߣ�������Ĳ���Ч�ʸ���
	
	um[2] = 6;
	um[3] = 1;
	um.insert(pair<int, int>(21, 51));

	um[4] = 4;
	um[5] = 6;
	um[6] = 99;

	unordered_map<int, int>::iterator cd;
	for (cd=um.begin();cd!=um.end();cd++)
	{
		cout << cd->first << ' ' << cd->second << endl;
	}

	/*unordered_map<int, int>::reverse_iterator t;
	for (cd = t.rbegin(); t!= um.rend(); cd++)
	{
		cout << t->first << ' ' << t->second << endl;
	}*/

	cout << endl;
	for (auto &i:um)
	{
		cout << i.first << ' ' << i.second<<endl;
	}
	cout << endl;
	//cd=um.find(21);
	cout << um[210];//û�з�����ʱ���ֵĶ���
	system("pause"); 
	return 0; 
}
//pair<iterator,bool> insert(const value_type & x)
