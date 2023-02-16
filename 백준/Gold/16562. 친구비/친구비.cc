#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 10'001

int n, m, k;
array<int, MAXN> costs;
array<int, MAXN> parents;
array<bool, MAXN> visit;

int Find(int x);
void Union(int a, int b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	iota(parents.begin(), parents.end(), 0);

	cin >> n >> m >> k;
	for (int& cost : costs | views::drop(1) | views::take(n) )
		cin >> cost;

	//문제해결
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		Union(u, v);
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int person = Find(i);
		if (!visit[person]) {
			visit[person] = true;
			ans += costs[person];
		}
	}

	if (ans <= k)
		cout << ans;
	else
		cout << "Oh no";

}

int Find(int x) {
	if (x == parents[x])
		return x;
	return parents[x] = Find(parents[x]);
}

void Union(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a > b)
		swap(a, b);

	costs[a] = min(costs[a], costs[b]);
	parents[b] = a;
}

