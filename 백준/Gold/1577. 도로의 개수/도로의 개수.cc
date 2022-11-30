#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define MAXN 101

int n, m, k;
array<array<ll, MAXN>, MAXN> dp;
vector<pair<pii, pii>> works;

bool Inside(int x, int y);
ll DP(int x, int y);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&dp[0][0], MAXN * MAXN, -1);

	cin >> n >> m >> k;
	++n; ++m;
	works.assign(k, {});
	for (auto& work : works)
		cin >> work.first.first >> work.first.second >> work.second.first >> work.second.second;

	//문제해결
	dp[0][0] = 1;
	ranges::sort(works);

	//출력
	cout << DP(n - 1, m - 1);

}

bool Inside(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

ll DP(int x, int y) {
	if (dp[x][y] != -1)
		return dp[x][y];

	dp[x][y] = 0;
	if (Inside(x - 1, y) && !ranges::binary_search(works, make_pair(make_pair(x, y), make_pair(x - 1, y))) && !ranges::binary_search(works, make_pair(make_pair(x - 1, y), make_pair(x, y))))
		dp[x][y] += DP(x - 1, y);
	if (Inside(x, y - 1) && !ranges::binary_search(works, make_pair(make_pair(x, y), make_pair(x, y - 1))) && !ranges::binary_search(works, make_pair(make_pair(x, y - 1), make_pair(x, y))))
		dp[x][y] += DP(x, y - 1);

	return dp[x][y];
}
