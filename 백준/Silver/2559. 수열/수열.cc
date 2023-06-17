#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <queue>

using namespace std;

int n, k;
vector<int> nums;
queue<int> q;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;

	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	int sum = 0;
	for (int i = 0; i < k; ++i) {
		q.push(nums[i]);
		sum += nums[i];
	}

	int ans = sum;
	for (int i = k; i < n; ++i) {
		sum -= q.front();
		q.pop();
		sum += nums[i];
		q.push(nums[i]);
		ans = max(ans, sum);
	}

	cout << ans;
	
}
