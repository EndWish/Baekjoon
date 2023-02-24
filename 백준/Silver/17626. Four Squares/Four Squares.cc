#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;

int Solved();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;

	//문제해결
	cout << Solved();

}

int Solved() {
	vector<int> nums;
	for (int i = 1; i <= n; ++i) {
		int num = i * i;
		if (num <= n)
			nums.push_back(num);
		else
			break;
	}

	// 1. 1개로 표현이 가능한 경우
	if (ranges::binary_search(nums, n))
		return 1;

	// 2. 2개로 표현이 가능한 경우
	for (int num : nums)
		if (ranges::binary_search(nums, n - num))
			return 2;

	// 3. 3개로 표현이 가능한 경우
	for (int num : nums) {
		int findNum = n - num;
		int s = 0, e = nums.size() - 1;
		while (s <= e) {
			int sum = nums[s] + nums[e];
			if (sum == findNum)
				return 3;
			if (sum < findNum)
				++s;
			else
				--e;
		}
	}

	return 4;
}