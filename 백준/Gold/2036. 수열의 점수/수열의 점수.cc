#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

ll n, ans;
vector<ll> nums1, nums2;

void func(vector<ll>& nums);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		if (num <= 0)
			nums2.push_back(num);
		else if (num == 1)
			ans += num;
		else
			nums1.push_back(num);
	}

	ranges::sort(nums1);
	ranges::sort(nums2, greater<ll>{});
	
	func(nums1);
	func(nums2);
	
	cout << ans;

}

void func(vector<ll>& nums) {
	while (!nums.empty()) {
		if (nums.size() == 1) {
			ans += *nums.rbegin();
			nums.pop_back();
		}
		else {
			ans += (*nums.rbegin()) * (*(nums.rbegin() + 1));
			nums.pop_back();
			nums.pop_back();
		}
	}
}