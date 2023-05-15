#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
#define piii pair<pii, int>

struct Vertex {
	int r, c, s;

	Vertex(int r, int c, int s) : r{ r }, c{ c }, s{ s }{
	}

};

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n, k, es, er, ec;
queue<Vertex> q;
array<array<int, 201>, 201> board;

bool IsInside(int r, int c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	
	vector<Vertex> viruses;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			cin >> board[r][c];
			if (board[r][c] != 0)
				viruses.emplace_back(board[r][c], r, c);
		}
	}
	cin >> es >> er >> ec;

	ranges::sort(viruses, [](const Vertex& a, const Vertex& b) {
		return a.r < b.r;
		});
	for (auto [virusNum, r, c] : viruses) {
		q.emplace(r, c, 0);
	}

	while (!q.empty()) {
		auto [r, c, s] = q.front();
		q.pop();

		if (s == es)
			continue;

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (!IsInside(nr, nc) || board[nr][nc] != 0)
				continue;
			board[nr][nc] = board[r][c];
			q.emplace(nr, nc, s + 1);
		}
	}

	cout << board[er][ec];

}

bool IsInside(int r, int c) {
	return 1 <= r && r <= n && 1 <= c && c <= n;
}

