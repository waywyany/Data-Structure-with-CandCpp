#include <iostream>
using namespace std;
#include <time.h>
#include <string>
#include "HashClass.h"
//#include "RBTree.h"
using namespace yellow::stl;

int main() {

	srand((unsigned)time(0));
	Hashset<int> a;
	for (int i = 0; i < 200; i++)a.insert(rand() % 541);
	
	a.showTable();
	/*cout << a.constain(1) << endl;
	cout << a.constain(64135) << endl;*/

	
	return 0;
}