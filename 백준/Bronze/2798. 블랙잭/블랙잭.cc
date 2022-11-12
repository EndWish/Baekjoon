#include <iostream>

using namespace std;
int n, m;
int result = 0;
int *a;

void f(int, int, int);

int main() {
	cin >> n >> m;
	a = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	for (int i = 0; i < n - 2; ++i) {
		f(3, i, 0);
	}
	

	cout << result;

	return 0;
}

void f(int num, int start, int sum) {
	if (num == 1) {
		sum += a[start];
		if (result < sum && sum <= m) {
			result = sum;
		}
		return;
	}

	for (int i = start + 1; i < n - num + 2; ++i) {
		f(num - 1, i, sum + a[start]);
	}
}