#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

#define pii pair<int,int>

int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };

int n, m;
array<array<vector<pii>, 101>, 101> buttons;
array<array<bool, 101>, 101> visit, light;
queue<pii> q;

bool IsInside(int r, int c);
void Print();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		buttons[x][y].emplace_back(a, b);
	}

	q.emplace(1, 1);
	visit[1][1] = true;
	light[1][1] = true;
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();

		// 불을 킨다.
		for (auto [br, bc] : buttons[r][c]) {
			if (light[br][bc])
				continue;

			light[br][bc] = true;
			
			// 불을 견 방의 인접한곳에 방문한 적이 있다면 해당 방도 방문이 가능하므로 큐에 넣는다.
			bool canMove = false;
			for (int i = 0; i < 4; ++i) {
				int nbr = br + dr[i];
				int nbc = bc + dc[i];
				if (IsInside(nbr, nbc) && visit[nbr][nbc]) {
					canMove = true;
					break;
				}
			}

			if (canMove) {
				q.emplace(br, bc);
				visit[br][bc] = true;
			}

		}

		// 현위치에서 인접한곳 중 이동해서 갈 수 있는 곳을 큐에 넣는다.
		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (IsInside(nr, nc) && !visit[nr][nc] && light[nr][nc]) {
				q.emplace(nr, nc);
				visit[nr][nc] = true;
			}
		}

		//Print();
	}

	int ans = 0;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			if (light[r][c])
				++ans;
		}
	}

	cout << ans;



}

bool IsInside(int r, int c) {
	return 1 <= r && r <= n && 1 <= c && c <= n;
}

void Print() {
	cout << "\n";
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			cout << light[r][c] << " ";
		}
		cout << "\n";
	}
}