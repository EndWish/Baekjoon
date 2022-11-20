#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
//#include <format>

using namespace std;

#define MAXN 501

struct Pos {
	int dmg = 0;
	int r;
	int c;

	Pos() {};
	Pos(int _dmg, int _r, int _c) : dmg{ _dmg }, r{ _r }, c{ _c }{};
	bool operator>(const Pos& other) const { return dmg > other.dmg; }
};

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m;
array<array<int, MAXN>, MAXN> board;	// 0 : 안전, 1 : 위험, 2 : 죽음
array<array<int, MAXN>, MAXN> visit;

void SetSection(int x1, int y1, int x2, int y2, int type);
bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&visit[0][0], MAXN * MAXN, -1);

	cin >> n;
	int x1, y1, x2, y2;

	for (int i = 0; i < n; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		SetSection(x1, y1, x2, y2, 1);
	}
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		SetSection(x1, y1, x2, y2, 2);
	}
	
	//문제해결
	priority_queue<Pos, vector<Pos>, greater<Pos>> pq;
	pq.emplace(0, 0, 0);
	while (!pq.empty()) {
		Pos pos = pq.top();
		pq.pop();

		if (visit[pos.r][pos.c] != -1)	// 이미 확정된 경우
			continue;
		visit[pos.r][pos.c] = pos.dmg;
		//cout << format("({},{}) : {} 으로 확정\n", pos.r, pos.c, pos.dmg);
		
		for (int i = 0; i < 4; ++i) {
			int nr = pos.r + dr[i];
			int nc = pos.c + dc[i];
			if (Inside(nr, nc) && visit[nr][nc] == -1) {	// 아직 확정되지 않은 곳일 경우
				if (board[nr][nc] == 0)	// 안전지역일 경우
					pq.emplace(pos.dmg, nr, nc);
				else if (board[nr][nc] == 1)	// 위험지역일 경우
					pq.emplace(pos.dmg + 1, nr, nc);
			}
		}
	}

	//출력
	cout << visit[500][500];

}

void SetSection(int x1, int y1, int x2, int y2, int type) {
	int left, right, up, down;
	left = min(x1, x2);
	right = max(x1, x2);
	up = max(y1, y2);
	down = min(y1, y2);

	for (int r = down; r <= up; ++r)
		for (int c = left; c <= right; ++c)
			board[r][c] = max(board[r][c], type);
}
bool Inside(int r, int c) {
	return 0 <= r && r < MAXN && 0 <= c && c < MAXN;
}