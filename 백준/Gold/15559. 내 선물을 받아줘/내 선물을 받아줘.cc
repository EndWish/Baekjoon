#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 1000
#define pii pair<int, int>

int n, m;
array<array<char, MAXN>, MAXN> board;
array<array<pii, MAXN>, MAXN> parents;
array<array<bool, MAXN>, MAXN> visit;

pii GetDelta(char ch);
bool Inside(int r, int c);
pii Find(int r, int c);
void Unite(pii pos1, pii pos2);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			parents[r][c] = make_pair(r, c);
		}
	}

	//문제해결
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			pii delta = GetDelta(board[r][c]);
			int nr = r + delta.first;
			int nc = c + delta.second;

			if (Inside(nr, nc)) {
				Unite({ r, c }, { nr, nc });
			}
		}
	}

	//출력
	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			auto [pr, pc] = Find(r, c);
			if (!visit[pr][pc]) {
				visit[pr][pc] = true;
				++ans;
			}
		}
	}
	cout << ans;

}

pii GetDelta(char ch) {
	switch (ch) {
	case 'N': return { -1 ,0 };
	case 'E': return { 0, +1 };
	case 'W': return { 0 ,-1 };
	case 'S': return { +1 ,0 };
	default:
		break;
	}
}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

pii Find(int r, int c) {
	int pr = parents[r][c].first;
	int pc = parents[r][c].second;

	if (pr == r && pc == c)	// 부모가 자기자신이면 
		return { r,c };

	parents[r][c] = Find(pr, pc);	// 부모가 자기자신이 아닐경우 부모갱신
	return parents[r][c];
}

void Unite(pii pos1, pii pos2) {
	pos1 = Find(pos1.first, pos1.second);
	pos2 = Find(pos2.first, pos2.second);

	if (pos1 <= pos2) {
		parents[pos2.first][pos2.second] = pos1;
	}
	else {
		parents[pos1.first][pos1.second] = pos2;
	}
}
