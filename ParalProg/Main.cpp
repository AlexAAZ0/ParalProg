
#include <iostream>
#include "pthread.h"
#pragma comment(lib,"pthreadVCE2.lib")

using namespace std;

void* right_rectangles(void* args) {
	Params* param = (Params*) args;

	cout << "Hello from func!\n";

	//printf("%d\n", param->a);
	return 0;
}


struct Params {

	float a;
	float b;
	float h;
	float result;
};

void input() {

}
int main() {
	pthread_t thr;
	int status_adr;

	int result = 0;

	int count;
	int limit_a;
	int limit_b;
	int steps;

	cout << "Enter the number of threads" << endl;
	cin >> count;

	cout << "Enter the integration limit" << endl;
	cin >> limit_a >> limit_b;

	cout << "Enter the steps" << endl;
	cin >> steps;


	float interval = abs(limit_b - limit_a) / count;

	float a = limit_a > limit_b ? limit_b : limit_a;

	float* x = new float[count];

	Params *params = new Params[count];

	for (int i = 0; i < count; i++) {
		//x[i] = a + i * interval;
		params[i].h = steps;
		params[i].a = a + i * interval;
		params[i].b = a + (i + 1) * interval;
		params[i].result = 0;
	}

	pthread_t* array = new pthread_t[count];

	for (int i = 0; i < count; i++) {
		int pid = pthread_create(&array[i], NULL, right_rectangles, &params[i]);

	}

	for (int i = 0; i < count; i++) {
		pthread_join(array[i], (void**)&status_adr);

	}

	cout << "Main Thread\r" << endl;

	return 0;
}