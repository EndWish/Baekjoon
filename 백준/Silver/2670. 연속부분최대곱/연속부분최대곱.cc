#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>

using namespace std;

int n;
array<long double, 10'000> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
		nums[i] = log10l(nums[i]);
	}

	//문제해결
	long double ans = -numeric_limits<long double>::max();
	long double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += nums[i];
		ans = max(sum, ans);
		
		if (sum < 0)
			sum = 0;
	}

	//출력
	cout.precision(3);
	cout << fixed << powl(10, ans);

}