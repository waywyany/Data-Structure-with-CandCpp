#include <iostream>
using namespace std;
#include "myVector.h"
#include <vector>
#include <time.h>
#include <string>
using namespace yellow::stl;

int main() {
	//标准模板和自己写的性能测试，insert函数使用了一些优化，速度大幅提高。
	//标准库插入5000个大概执行4.4s，自己的库大概执行0.003s
	//优化本质上应该是将在for循环中的元素移动改为了内存整块移动
	vector<bool> vec;
	clock_t t1, t2,t3,t4;
	t1 = clock();
	for (int i = 0; i < 5000; i++) {
		vec.insert(vec.begin(), true);
	}
	t2 = clock();
	printf("standard vector 耗时了 %lf s\n", (double)((t2 - t1) / 1.0 / CLOCKS_PER_SEC));
	 
	Vector<bool> vec2;
	t3 = clock();
	for (int i = 0; i < 10000; i++) {
		vec2.insert(vec2.begin(), true);
	}
	t4 = clock();
	printf("my vector 耗时了 %e s\n", (double)((t4 - t3) / 1.0 / CLOCKS_PER_SEC));
	

}