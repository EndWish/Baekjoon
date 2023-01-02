#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

int n;
vector<string> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	for (string& num : nums)
		cin >> num;

	//문제해결
	auto func = [](const string& a, const string& b) {
		string ab = a + b;
		string ba = b + a;
		return ab > ba;
	};
	ranges::sort(nums, func);

	//출력
	if (nums[0][0] == '0')
		cout << 0;
	else {
		for (const string& num : nums)
			cout << num;
	}
}