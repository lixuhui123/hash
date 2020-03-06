//#include <iostream>
//#include<vector>
//using namespace std;
//int main()
//{
//	vector<int> m_v;
//	m_v.push_back(1);
//	m_v.push_back(2);
//	m_v.push_back(3);
//	m_v.push_back(4);
//	m_v.push_back(6);
//	m_v.push_back(5);
//
//	m_v.reserve(30);
//
//	for (auto &e : m_v)
//	{
//		cout << e << endl;
//	}
//	cout << m_v.size()<<endl;
//	cout << m_v.capacity() << endl;
//
//
//	
// 	system("pause"); 
//	return 0;
//}



#include <iostream>
#include <vector>

int main()
{
	std::vector<int> foo(3, 100);   // three ints with a value of 100
	std::vector<int> bar(5, 200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
	system("pause");
	return 0;
}