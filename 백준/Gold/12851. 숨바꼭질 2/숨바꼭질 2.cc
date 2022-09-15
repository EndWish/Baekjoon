#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 200'000
#define INF numeric_limits<int>::max()

using namespace std;

int n, k;
int dp[MAXN];
int cnt[MAXN];

pair<int, int> BFS(int start, int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;

	//문제해결
	auto [dist, count] = BFS(n, k);
	cout << dist << "\n" << count;

	//출력

}

pair<int,int> BFS(int start, int end) {
	fill_n(&dp[0], MAXN, -1);

	queue<int> q;
	q.push(start);
	dp[start] = 0;
	cnt[start] = 1;

	while (!q.empty()) {
		int pos = q.front();
		q.pop();

		int nextPos[] = { pos - 1, pos + 1, pos * 2 };
		for (int i = 0; i < 3; ++i) {
			if (0 <=nextPos[i] && nextPos[i] < MAXN) {
				
				if (dp[nextPos[i]] == -1) {
					dp[nextPos[i]] = dp[pos] + 1;
					q.push(nextPos[i]);
				}

				if (dp[pos] + 1 == dp[nextPos[i]])
					cnt[nextPos[i]] += cnt[pos];
			}
		}
	}

	return { dp[end], cnt[end] };
}
