#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
#define MAXN 50

const int WALL = -1;
const int BLANK = -2;
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1 ,0,0 };

int n, m;
array<array<int, MAXN>, MAXN> originBoard, board;
array<array<bool, MAXN>, MAXN> inactiveVirusBoard;
vector<pii> viruses;
vector<int> active;

int DFS();
bool IsInside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> originBoard[r][c];
			switch (originBoard[r][c]) {
			case 0: originBoard[r][c] =  BLANK; break;
			case 1: originBoard[r][c] =  WALL; break;
			case 2: 
				originBoard[r][c] = BLANK;
				viruses.emplace_back(r, c);
				break;
			default:
				break;
			}

		}
	}

	active.assign(viruses.size(), false);
	fill_n(active.end() - m, m, true);
	
	//문제해결
	int ans = numeric_limits<int>::max();
	do {
		int result = DFS();
		if (result == -1)
			continue;
		ans = min(ans, result);
	} while (ranges::next_permutation(active).found);

	if (ans == numeric_limits<int>::max())
		cout << -1;
	else
		cout << ans;
}

int DFS() {
	queue<pii> q;

	board = originBoard;
	for (int i = 0; i < viruses.size(); ++i) {
		auto [r, c] = viruses[i];
		inactiveVirusBoard[r][c] = !active[i];
		if (active[i]) {
			board[r][c] = 0;
			q.emplace(r, c);
		}
	}

	// BFS 수행
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			// 빈칸일 경우 바이러스를 퍼트린다.
			if (IsInside(nr, nc) && board[nr][nc] == BLANK) {
				board[nr][nc] = board[r][c] + 1;
				q.emplace(nr, nc);
			}
		}
	}

	// 모든 칸에 바이러스가 존재하는지 확인
	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (board[r][c] != WALL) {
				// 방문하지 않았고 비활성화 바이러스도 없다면 실패
				if (board[r][c] == BLANK && !inactiveVirusBoard[r][c])
					return -1;
				if (board[r][c] != BLANK && !inactiveVirusBoard[r][c])
					ans = max(ans, board[r][c]);
			}
		}
	}

	// 결과 리턴
	return ans;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}
