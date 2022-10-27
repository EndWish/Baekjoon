#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int t;
array<int, 10> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		for (int& num : nums)
			cin >> num;

		//문제해결
		ranges::sort(nums, greater<int>());

		//출력
		cout << nums[2] << "\n";
	}


}