#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
//#include <format>

using namespace std;

int length, width, height;
int n;
array<int, 20> cubes;

bool pushCube(int l, int w, int h);
void setMul(int& x, int y, int z, int dist, int cubeLength, int i);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int sum = 0;
	cin >> length >> width >> height;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		cin >> cubes[input];
		sum += cubes[input];
	}

	if (!pushCube(length, width, height)) {
		cout << -1;
		return 0;
	}

	int lateCount = 0;
	for (int i = 0; i < 20; ++i) {
		lateCount += cubes[i];
	}

	cout << sum - lateCount;
}

bool pushCube(int l, int w, int h) {
	if (l == 0 || w == 0 || h == 0)
		return true;

	int i = 19;
	while (0 <= i) {
		if (0 < cubes[i] && (1 << i) <= min({ l, w, h }))
			break;
		--i;
	}
	if (i == -1)
		return false;

	// 사용할 큐브의 개수를 계산한다.
	int cubeLength = (1 << i);
	int mul[3] = {1,1,1};
	int x = 1, y = 1, z = 1;
	setMul(x, y, z, l, cubeLength, i);
	setMul(y, x, z, w, cubeLength, i);
	setMul(z, x, y, h, cubeLength, i);
	//cout << format("{}종류의 큐브를 {}x{}x{}개 사용\n", i, x, y, z);

	// 큐브를 사용한다.
	cubes[i] -= x * y * z;

	// 분할정복을 한다.
	array<int, 2> lLength = { x * cubeLength, l - x * cubeLength };
	array<int, 2> wLength = { y * cubeLength, w - y * cubeLength };
	array<int, 2> hLength = { z * cubeLength, h - z * cubeLength };
	for (int a = 0; a < 2; ++a) {
		for (int b = 0; b < 2; ++b) {
			for (int c = 0; c < 2; ++c) {
				if (a == 0 && b == 0 && c == 0)
					continue;
				if (!pushCube(lLength[a], wLength[b], hLength[c]))
					return false;
			}
		}
	}

	return true;
}

void setMul(int& x, int y, int z, int dist, int cubeLength, int i) {
	while (x < dist / cubeLength) {
		if ((x + 1) * y * z > cubes[i])
			break;
		++x;
	}
}