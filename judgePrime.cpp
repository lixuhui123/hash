#include <iostream>
#include <cmath>
#include<stdio.h>
using namespace std;
bool judgePrime(unsigned int tmp)
{
	int gen = (int)sqrt(tmp);//Еїба
	//int gen = (int)tmp/2;

	int i = 2;
	for (i=2;i<gen;++i)
	{
		if (tmp % i==0)
		{
			return false;
		}
	}
	return true;
}
int maindeewwe()
{
    unsigned long long max = 3E9;
	unsigned long long i = 0;
	unsigned long long j = 0;
	int cont = -1;
	for (i=22;i<max;i*=2)
	{
		for (j = i; !judgePrime(j); j++);
		
		cont++;
		if (cont%5==0)
		{
			cout << endl;
		}
		printf("%11lld,",j);
			
		
	}
	system("pause"); 
	return 0;
}