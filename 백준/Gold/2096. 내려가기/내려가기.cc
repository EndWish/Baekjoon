#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 100'000
#define INF numeric_limits<int>::max()

using namespace std;

int n;
int num[MAXN][3];
int dpMax[2][3];
int dpMin[2][3];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> num[i][0] >> num[i][1] >> num[i][2];

	//문제해결
	copy_n(&num[0][0], 3, &dpMax[0][0]);
	copy_n(&num[0][0], 3, &dpMin[0][0]);
	for (int i = 1; i < n; ++i) {
		fill_n(&dpMax[1][0], 3, 0);
		fill_n(&dpMin[1][0], 3, INF);
		for (int x = 0; x < 3; ++x) {
			for (int dx = -1; dx <= 1; ++dx) {
				int nx = x + dx;
				if (nx < 0 || 2 < nx)
					continue;
				dpMax[1][nx] = max(dpMax[1][nx], dpMax[0][x] + num[i][nx]);
				dpMin[1][nx] = min(dpMin[1][nx], dpMin[0][x] + num[i][nx]);
			}
		}
		copy_n(&dpMax[1][0], 3, &dpMax[0][0]);
		copy_n(&dpMin[1][0], 3, &dpMin[0][0]);
	}

	//출력
	cout << *max_element(&dpMax[0][0], &dpMax[0][0] + 3) << " ";
	cout << *min_element(&dpMin[0][0], &dpMin[0][0] + 3) << " ";

}

