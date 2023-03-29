#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 20
#define pii pair<int,int>

int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

int n, m, f;
array<array<int, MAXN>, MAXN> board;
array<array<int, MAXN>, MAXN> visit;
array<array<int, MAXN>, MAXN> customers;
vector<pii> goals;

pii taxi;

void BFS(int sr, int sc);
pii GetNearestCumtomerPos();
bool IsInside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> f;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}
	cin >> taxi.first >> taxi.second;
	--taxi.first;
	--taxi.second;

	goals.assign(m + 1, {});
	for (int i = 1; i <= m; ++i) {
		int sr, sc, er, ec;
		cin >> sr >> sc >> er >> ec;
		customers[--sr][--sc] = i;
		goals[i] = { --er, --ec };
	}

	// 손님이 없을때 까지 택시운행하기
	int count = m;
	while (0 < count) {
		// 가장 가까운 손님에게 이동
		BFS(taxi.first, taxi.second);
		pii cumtomerPos = GetNearestCumtomerPos();
		if (!IsInside(cumtomerPos.first, cumtomerPos.second)) break;	// 경로가 없다면 여기서 끝낸다.
		taxi = cumtomerPos;	// 택시의 위치를 손님의 위치로 이동시킨다.
		f -= visit[cumtomerPos.first][cumtomerPos.second];	// 연로를 감소시킨다.
		int customerNum = customers[cumtomerPos.first][cumtomerPos.second];		// 손님의 번호를 기억한다.(목적지를 알기위해)
		customers[cumtomerPos.first][cumtomerPos.second] = 0;	// 손님을 제거한다.
		if (f < 0) break;	// 연료가 부족한지 확인한다.

		// 손님을 목적지로 이동시킨다.
		BFS(taxi.first, taxi.second);
		pii goal = goals[customerNum];
		if (visit[goal.first][goal.second] == -1) break;	// 경로가 없다면 여기서 끝낸다.
		taxi = goal;	// 택시를 목적지로 이동시킨다.
		f -= visit[goal.first][goal.second];	// 연료를 감소시킨다.
		if (f < 0) break; // 연료가 부족한지 확인한다.
		f += visit[goal.first][goal.second] * 2;	// 연료를 두배로 받는다.
		--count;	// 남은 손님수를 감소시킨다.
	}

	if (0 < count)
		cout << -1;
	else
		cout << f;

}

void BFS(int sr, int sc) {
	fill_n(&visit[0][0], MAXN * MAXN, -1);

	queue<pii> q;
	q.emplace(sr, sc);
	visit[sr][sc] = 0;
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (IsInside(nr, nc) && board[nr][nc] == 0 && visit[nr][nc] == -1) {
				q.emplace(nr, nc);
				visit[nr][nc] = visit[r][c] + 1;
			}
		}
	}
}
pii GetNearestCumtomerPos() {
	int minDistance = numeric_limits<int>::max();
	int ansR = -1, ansC = -1;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (customers[r][c] != 0 && visit[r][c] != -1 && visit[r][c] < minDistance) {
				minDistance = visit[r][c];
				ansR = r;
				ansC = c;
			}
		}
	}
	return { ansR, ansC };
}
bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}
