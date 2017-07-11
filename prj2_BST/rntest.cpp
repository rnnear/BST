#include<iostream>
#include<vector>
#include"rnBST.h"
using namespace std;
int main()
{
	vector<int> rnvec = {5, 45, 12, 3, 65, 1, 6, 455, -12, 23, -1, -45, -9};
	BST<int> rnbst(rnvec);
	rnbst.MiddleTrav(cout);
}
