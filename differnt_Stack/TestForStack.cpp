#include <iostream>
using namespace std;
#include "mystack.h"
#include "myListStack.h"
#include <time.h>
#include <string>
using namespace yellow::stl;

int main() {

	clock_t t1, t2,t3,t4;
	Stack<int> sta;
	int iteration = 0;
	t1 = clock();
	while (iteration < 200000) {
		
		for (int i = 0; i < 100; i++) {
			sta.push_back(rand()%137);
		}
		/*for (int i = 0; i < 10000; i++) {
			sta.pop();
		}*/
		iteration++;
	}
	t2 = clock();
	printf("耗时： %lf s\n", (double)((t2 - t1) / 1.0 / CLOCKS_PER_SEC));

	ListStack<int> sta2;
	iteration = 0;
	t3 = clock();
	while (iteration < 200000) {

		for (int i = 0; i < 100; i++) {
			sta2.push_back(rand() % 137);
		}
		/*for (int i = 0; i < 10000; i++) {
			sta.pop();
		}*/
		iteration++;
	}
	t4 = clock();
	printf("耗时了 %lf s\n", (double)((t4 - t3) / 1.0 / CLOCKS_PER_SEC));

	return 0;
}
