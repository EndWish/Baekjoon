#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

array<int, 8> arr;
array<bool, 8> visit;

bool ConvexHull();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	for (int& v : arr)
		cin >> v;

	//문제해결
	int mul = 1;
	for (int i = 0; i < 8; ++i) {
		if (!visit[i]) {
			visit[i] = true;
			int count = 1;
			for (int j = i + 1; j < 8; ++j) {
				if (arr[i] == arr[j]) {
					visit[j] = true;
					++count;
					mul *= count;
				}
			}
		}
	}

	int ans = 0;
	ranges::sort(arr);
	do {
		if (ConvexHull()) {
			ans += mul;
		}
			
	} while (ranges::next_permutation(arr).found);

	//출력
	cout << ans;
}

bool ConvexHull() {
	// m.x = L/(L/R + 1), m.y = L/(L/R + 1)
	// m^2 = 2*(m.x^2)
	// M^2 >= 2*((LR/(L/ + R))^2)

	bool res = true;
	for (int m = 0; m < 8; ++m) {
		int l = m - 1 >= 0 ? m - 1 : 7;
		int r = m + 1 < 8 ? m + 1 : 0;

		double M = arr[m], L = arr[l], R = arr[r];

		if (M * M < 2 * ( (L * R / (L + R)) * (L * R / (L + R))) ) {
			res = false;
			break;
		}
	}
	return res;
}
