#include <iostream>
using namespace std;
#include "myVector.h"
#include <vector>
#include <time.h>
#include <string>
using namespace yellow::stl;

int main() {
	//��׼ģ����Լ�д�����ܲ��ԣ�insert����ʹ����һЩ�Ż����ٶȴ����ߡ�
	//��׼�����5000�����ִ��4.4s���Լ��Ŀ���ִ��0.003s
	//�Ż�������Ӧ���ǽ���forѭ���е�Ԫ���ƶ���Ϊ���ڴ������ƶ�
	vector<bool> vec;
	clock_t t1, t2,t3,t4;
	t1 = clock();
	for (int i = 0; i < 5000; i++) {
		vec.insert(vec.begin(), true);
	}
	t2 = clock();
	printf("standard vector ��ʱ�� %lf s\n", (double)((t2 - t1) / 1.0 / CLOCKS_PER_SEC));
	 
	Vector<bool> vec2;
	t3 = clock();
	for (int i = 0; i < 10000; i++) {
		vec2.insert(vec2.begin(), true);
	}
	t4 = clock();
	printf("my vector ��ʱ�� %e s\n", (double)((t4 - t3) / 1.0 / CLOCKS_PER_SEC));
	

}