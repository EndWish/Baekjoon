#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define INF numeric_limits<int>::max()

int n;
int len;
array<int, 11> num;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;

	//문제해결
	int count = -1;
	while (true) {
		++count;

		// 다음 단계로 이동
		bool upgrade = false;

		// 1. 첫번째 자리부터 숫자를 올려도 되는지 확인한다.
		for (int i = 0; i < len - 1; ++i) {
			if (num[i] + 1 < num[i + 1]) {
				++num[i];
				iota(num.begin(), num.begin() + i, 0);
				upgrade = true;
				break;
			}
		}
		if (0 < len && !upgrade && num[len - 1] < 9) {
			++num[len - 1];
			iota(num.begin(), num.begin() + len - 1, 0);
			upgrade = true;
		}

		// 2. 다음자리수로 확장한다.
		if (!upgrade) {
			++len;
			iota(num.begin(), num.begin() + len, 0);

			if (10 < len) {	// 불가능한 경우
				cout << -1;
				break;
			}
		}

		// 끝날 조건
		if (count == n) {
			for (int i = len - 1; i >= 0; --i)
				cout << num[i];
			break;
		}
	}

	//출력
}
