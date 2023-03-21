#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
#define MAXN 12

int dr[] = { 0, 0, 0, -1, 1 };
int dc[] = { 0, 1, -1 , 0,0 };

int n, k;
array<array<int, MAXN>, MAXN> board;
array<array<vector<pii>, MAXN>, MAXN> horses;	// = (번호, 방향)
vector<pii> horsesPos;	// = 위치

bool IsInside(int r, int c);
pii Move(int horseNum);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}

	horsesPos.assign(k + 1, {});
	for (int i = 1; i <= k; ++i) {
		int r, c, d;
		cin >> r >> c >> d;
		--r;
		--c;
		horses[r][c].emplace_back(i, d);
		horsesPos[i] = { r, c };
	}

	for (int turn = 1; turn <= 1000; ++turn) {
		// 모든 말을 한번씩 움직인다.
		for (int i = 1; i <= k; ++i) {
			auto [moveR, moveC] = Move(i);
			if (4 <= horses[moveR][moveC].size()) {
				cout << turn;
				return 0;
			}
		}
	}
	cout << -1;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}

pii Move(int horseNum) {

	auto[r, c] = horsesPos[horseNum];
	auto it = ranges::find(horses[r][c], horseNum, &pii::first);
	int d = it->second;

	int nr = r + dr[d];
	int nc = c + dc[d];

	// 파란색(2)또는 맵밖일 경우
	if (!IsInside(nr, nc) || board[nr][nc] == 2) {
		// 방향을 반대로 바꾼다.
		it->second = (it->second == 1 || it->second == 3) ? it->second + 1 : it->second - 1;

		// 이동할 위치를 다시 계산한다.
		d = it->second;
		nr = r + dr[d];
		nc = c + dc[d];

		// 반대 방향도 막혀있을 경우 움직이지 않는다.
		if (!IsInside(nr, nc) || board[nr][nc] == 2) {
			return { r, c };
		}
	}

	// 말들의 위치를 바꿔준다.
	for (auto iter = it; iter != horses[r][c].end(); ++iter)
		horsesPos[iter->first] = { nr, nc };

	// 말들을 옮긴다.
	if (board[nr][nc] == 0) {	// 흰색(0)일 경우
		horses[nr][nc].insert(horses[nr][nc].end(), it, horses[r][c].end());
	}
	else if (board[nr][nc] == 1) {	// 빨간색(1)일 경우
		vector<pii> temp;
		temp.insert(temp.end(), it, horses[r][c].end());
		ranges::reverse(temp);
		horses[nr][nc].insert(horses[nr][nc].end(), temp.begin(), temp.end());
	}

	// 이전위치에서는 삭제해준다.
	horses[r][c].erase(it, horses[r][c].end());
	return { nr, nc };

}
