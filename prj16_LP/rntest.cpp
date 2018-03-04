#include<iostream>
using namespace std;

void rnfun(const int** rnptr){}
int main()
{
	int rna = 0;
	const int* rnptr = &rna;
	const int** rnptt = &rnptr;
	rnfun(rnptt);
}
