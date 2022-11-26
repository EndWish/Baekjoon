#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n;
vector<int> bigs;
vector<int> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	bigs.assign(n, {});
	for (int& big : bigs)
		cin >> big;
	nums.assign(n, {});
	iota(nums.begin(), nums.end(), 1);

	//문제해결
	do {
		bool success = true;
		for (int i = 1; i <= n; ++i) {
			int count = 0;
			for (int j = 0; j < n; ++j) {
				if (nums[j] == i)
					break;
				if (i < nums[j])
					++count;
			}

			if (count != bigs[i - 1]) {
				success = false;
				break;
			}
		}

		if (success) {
			for (int num : nums)
				cout << num << " ";
			break;
		}
	} while (ranges::next_permutation(nums).found);

	//출력

}
