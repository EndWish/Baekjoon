#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0 ,-1,1 };

#define pii pair<int,int>

using namespace std;

int n, m;
int board[100][100];
int blank[100][100];
bool visit[100][100];

bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			cin >> board[r][c];

	//문제해결
	int ans = 0;
	priority_queue<pair<int, pii>> pq;
	pq.emplace(-0, make_pair(0,0));
	while (!pq.empty()) {
		auto [t, pos] = pq.top();
		t = -t;
		pq.pop();

		ans = max(ans, t);

		for (int i = 0; i < 4; ++i) {
			int nr = pos.first + dr[i];
			int nc = pos.second + dc[i];
			if (Inside(nr, nc) && !visit[nr][nc]) {
				if (board[nr][nc] == 1) {	// 치즈일 경우
					if (++blank[nr][nc] >= 2) {	// 공기와 접촉+, 2이상일 경우
						pq.emplace(-(t + 1), make_pair(nr, nc));
						visit[nr][nc] = true;
					}
				}
				else {	// 빈공간 일 경우
					pq.emplace(-t, make_pair(nr, nc));
					visit[nr][nc] = true;
				}
			}
		}

	}

	//출력
	cout << ans;

}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}