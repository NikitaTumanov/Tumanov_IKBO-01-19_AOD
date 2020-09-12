#include <iostream>
#include <ctime>
#include <cmath>
#include <queue>

using namespace std;
int k = 0;
static const int N = 10;
void input(int a[N]) {
	int max = -1;
	srand(time(0));
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 999;
		if (max < a[i]) {
			max = a[i];
		}
	}
	while (max != 0) {
		max /= 10;
		k++;
	}
}

void show(int a[N]) {
	for (int i = 0; i < N; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void sort(int a[N], queue <int> q[10]) {
	double count = 0;
	while (k != 0) {
		for (int j = 0; j < N; j++) {
			q[(a[j] % (int)pow(10.0, count + 1)) / (int)pow(10, count)].push(a[j]);
		}
		k--;
		count++;
		int j = 0;
		for (int i = 0; i < 10; i++) {
			while (!q[i].empty()) {
				a[j] = q[i].front();
				q[i].pop();
				j++;
			}
		}
	}
}

int main()
{
	int a[N];
	queue <int> q[10];
	input(a);
	show(a);
	sort(a, q);
	show(a);
	return 0;
}