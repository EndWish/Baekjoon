#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXM 1000
#define ll long long

using namespace std;

int n, m;
vector<int> nums;
vector<int> sums;
ll ans[MAXM];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	nums.assign(n + 1, 0);
	for (int& num : nums | views::drop(1)) {
		cin >> num;
		num %= m;
	}
	sums.assign(n + 1, 0);
	sums[0] = nums[0];
	for (int i = 1; i < sums.size(); ++i) {
		sums[i] = (sums[i - 1] + nums[i]) % m;
	}

	//문제해결
	for (int i = 0; i < sums.size(); ++i) {
		++ans[sums[i]];
	}
	for (int i = 0; i < m; ++i) {
		ans[i] = ans[i] * (ans[i] - 1) / 2;
	}

	//출력
	cout << reduce(&ans[0], &ans[0] + m);

}
