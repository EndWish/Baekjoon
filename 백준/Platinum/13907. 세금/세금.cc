#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 1001
#define INF numeric_limits<int>::max()
#define pii pair<int,int>
#define tup tuple<int,int,int>

using namespace std;

int n, m, k;
int s, d;
vector<pii> edge[MAXN];
int dp[MAXN][MAXN];
bool finished[MAXN][MAXN];

void Dijkstra(int start);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	cin >> s >> d;
	int a, b, w;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> w;
		edge[a].emplace_back(w, b);
		edge[b].emplace_back(w, a);
	}

	//문제해결
	fill_n(&dp[0][0], MAXN * MAXN, INF);
	Dijkstra(s);

	//출력
	cout << *ranges::min_element(dp[d]) << "\n";
	int p;
	int plusCost = 0;
	for (int i = 0; i < k; ++i) {
		cin >> p;
		plusCost += p;
		int ans = INF;
		for (int via = 0; via < n; ++via) {
			if (dp[d][via] != INF) {
				ans = min(ans, dp[d][via] + via * plusCost);
			}
		}
		cout << ans << "\n";
	}

}

void Dijkstra(int start) {
	priority_queue<tup> pq;	// -w, node, 거쳐간 횟수
	dp[start][0] = 0;
	pq.emplace(-0, start, 0);
	while (!pq.empty()) {
		auto [w, node, via] = pq.top();
		w *= -1;
		pq.pop();

		if (finished[node][via])
			continue;
		finished[node][via] = true;

		if (via >= n - 1)
			continue;

		for (int i = 0; i < edge[node].size(); ++i) {
			auto[cost, nextNode] = edge[node][i];
			if (dp[node][via] + cost < dp[nextNode][via + 1]) {
				dp[nextNode][via + 1] = dp[node][via] + cost;
				pq.emplace(-dp[nextNode][via + 1], nextNode, via + 1);
			}
		}

	}

}
