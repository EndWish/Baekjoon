#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>

using namespace std;

#define ll long long

int n, c;
int priority = 1000;
unordered_map<ll, pair<int, int>> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> c;
	
	//문제해결
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		if (nums.contains(num)) {	// 있을 경우
			++nums[num].first;
		}
		else {
			nums.emplace(num, make_pair( 1, priority-- ));
		}
	}

	vector<pair<ll, pair<int, int>>> ans(nums.begin(), nums.end());
	ranges::sort(ans, greater<>{}, & pair<ll, pair<int, int>>::second);

	//출력
	for (auto [num, count] : ans) {
		for (int i = 0; i < count.first; ++i)
			cout << num << " ";
	}

}
