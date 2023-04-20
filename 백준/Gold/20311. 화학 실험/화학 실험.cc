#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, k;
priority_queue<pii> pq;	// 개수, 색깔
pii temp;
vector<int> ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	for (int i = 1; i <= k; ++i) {
		int num;
		cin >> num;
		pq.emplace(num, i);
	}

	temp = { 0, -1 };
	for (int i = 0; i < n; ++i) {
		if (pq.empty()) {
			cout << -1;
			return 0;
		}

		pii x = pq.top();
		pq.pop();

		ans.push_back(x.second);
		--x.first;
		
		if (temp.first != 0) {
			pq.push(temp);
		}
		temp = x;
	}

	for (int num : ans)
		cout << num << " ";
	
}
