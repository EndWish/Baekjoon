#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 101
#define INF numeric_limits<int>::max()

using namespace std;

int n, m, r;
int item[MAXN];
array< array<int, MAXN>, MAXN> edge;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&edge[0][0], MAXN * MAXN, INF);
	for (int i = 0; i < MAXN; ++i)
		edge[i][i] = 0;

	cin >> n >> m >> r;
	for (int i = 1; i <= n; ++i)
		cin >> item[i];

	int a, b, l;
	for (int i = 0; i < r; ++i) {
		cin >> a >> b >> l;
		edge[a][b] = min(edge[a][b], l);
		edge[b][a] = min(edge[b][a], l);
	}

	//문제해결
	for (int via = 1; via <= n; ++via) {
		for (int from = 1; from <= n; ++from) {
			if (via == from)
				continue;

			for (int to = 1; to <= n; ++to) {
				if (from == to || via == to)
					continue;
				if (edge[from][via] == INF || edge[via][to] == INF)
					continue;

				// 경유하는 거리가 더 적으면 업데이트
				int dist = edge[from][via] + edge[via][to];
				if (dist < edge[from][to])
					edge[from][to] = dist;
			}
		}
	}

	//출력
	int ans = 0;
	for (int from = 1; from <= n; ++from) {
		int sum = 0;
		for (int to = 1; to <= n; ++to) {
			if (edge[from][to] <= m)
				sum += item[to];
		}
		ans = max(ans, sum);
	}
	cout << ans;

}

