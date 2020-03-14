#include <iostream>
#include "hashTable.h"
using namespace std;
using namespace lxh;
int mainuiyfuky()
{
	hashTable<int, int,dealint> ht;
	ht.insert(pair<int, int>(1, 5));
	ht.insert(pair<int, int>(3, 5));
	ht.insert(pair<int, int>(4, 5));
	ht.insert(pair<int, int>(33, 5));
	ht.insert(pair<int, int>(44, 5));
	ht.insert(pair<int, int>(6, 5));//

	hashTable<string, int,dealstr> test;
	test.insert(pair<string, int>("deee", 1));
	test.insert(pair<string, int>("dewd", 1));
	test.insert(pair<string, int>("dsa", 1));
	test.insert(pair<string, int>("dsa", 1));


	system("pause"); 
	return 0;
}