#include <iostream>
#include <array>
#include <numeric>
#include <cmath>

#define MAXN 100'000

using namespace std;

int b;
array<int, MAXN> arr;

int ArithmeticSequence(int start, int difference);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> b;
	for (int i = 0; i < b; ++i)
		cin >> arr[i];

	//문제해결
	if (b <= 2) {
		cout << 0;
		return 0;
	}

	int ans = numeric_limits<int>::max();
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			int start = arr[0] + i;
			int seceond = arr[1] + j;
			ans = std::min(ans, ArithmeticSequence(start, seceond - start));
		}
	}
	
	//출력
	if (ans == numeric_limits<int>::max()) {
		cout << -1;
	}
	else {
		cout << ans;
	}

}

int ArithmeticSequence(int start, int difference) {
	int res = 0;
	if (start != arr[0])
		++res;

	for (int i = 1; i < b; ++i) {
		start += difference;
		if (start == arr[i]) {	// 수가 일치하는 경우
			continue;
		}
		else if (abs(start - arr[i]) == 1) {	// 1만큼 차이나는 경우
			++res;
		}
		else {	// 불가능한 경우
			return  numeric_limits<int>::max();
		}
	}

	return res;
}
