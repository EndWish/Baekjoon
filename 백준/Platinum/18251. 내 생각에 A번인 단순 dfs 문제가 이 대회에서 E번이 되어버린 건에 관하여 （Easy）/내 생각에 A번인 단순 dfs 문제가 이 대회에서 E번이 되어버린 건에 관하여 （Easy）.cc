#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pil pair<int,ll>
#define INF numeric_limits<ll>::max()

// k는 최대 1~18
int n, k;
vector<int> nums;
vector<pil> points;	// (높이{0~17}, 가중치)

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n + 1, {});
	for (int& num : nums | views::drop(1))
		cin >> num;

	int nNode = n;
	while (0 < nNode) {
		nNode >>= 1;
		++k;
	}

	//문제해결
	ll ans = -INF;
	DFS(1);
	for (int i = 0; i < k; ++i) {
		for (int j = i; j < k; ++j) {
			ll sum = -INF;
			for (auto [y, w] : points) {
				if (y < i || j < y)
					continue;

				if (sum < 0) {
					sum = w;
				}
				else {
					sum += w;
				}
				ans = max(ans, sum);
			}
		}
	}

	cout << ans;
}

int DFS(int node) {
	// 리프노드가 아닐경우
	if (node * 2 <= n) {
		int subTreeHeight = DFS(node * 2);
		points.emplace_back(subTreeHeight + 1, nums[node]);
		DFS(node * 2 + 1);
		return subTreeHeight + 1;
	}

	// 리프노드일 경우
	points.emplace_back(0, nums[node]);
	return 0;

}
