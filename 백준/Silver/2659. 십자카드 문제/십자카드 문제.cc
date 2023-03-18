#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

bool IsClockNum(int num);
int GetClockNum(int num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	int num = 0;
	for (int i = 0; i < 4; ++i) {
		int input;
		cin >> input;
		num = num * 10 + input;
	}

	//문제해결
	num = GetClockNum(num);

	int ans = 1;
	for (int prev = 1111; prev < num; ++prev) {
		if (IsClockNum(prev))
			++ans;
	}
	cout << ans;
}

bool IsClockNum(int num) {
	int num2 = num;
	while (0 < num2) {
		if (num2 % 10 == 0)
			return false;
		num2 /= 10;
	}

	if (num != GetClockNum(num))
		return false;

	return true;
}

int GetClockNum(int num) {
	int result = num;
	for (int i = 0; i < 3; ++i) {
		int temp = num % 10;
		num = num / 10 + temp * 1000;
		result = min(result, num);
	}
	return result;
}
