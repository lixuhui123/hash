#include <iostream>
#include <string>
#include <unordered_map>

int maincdscsec()
{
	std::unordered_map<std::string, double> mymap = {
	   {"mom",5.4},
	   {"dad",6.1},
	   {"bro",5.9} };

	std::string input;
	std::cout << "who? ";
	getline(std::cin, input);

	std::unordered_map<std::string, double>::const_iterator got = mymap.find(input);
	/* 如果找到了，就返回一个迭代器，否则就返回unordered_map::end(容器末尾的元素)的迭代器。 */
	if (got == mymap.end())
		std::cout << "not found";
	else
		std::cout << got->first << " is " << got->second;

	std::cout << std::endl;
	system("pause");
	return 0;
}