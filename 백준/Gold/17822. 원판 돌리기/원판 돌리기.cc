#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

int di[] = { 0,0,-1,1 };
int dj[] = { -1,1,0,0 };

int n, m, t;
vector<vector<int>> board;	// board[i][j] = i번째 원판의 j번재 숫자

void Rotate(int x, int d, int k);
bool Remove();
void Modify();
bool IsInside(int i, int j);
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> t;
	board.assign(n, vector<int>(m, 0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> board[i][j];
		}
	}
	
	int x, d, k;
	while (t-- > 0) {
		cin >> x >> d >> k;
		Rotate(x, d, k);
		if (!Remove())
			Modify();
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if(board[i][j] != INF)
				ans += board[i][j];
		}
	}
	cout << ans;

}

void Rotate(int x, int d, int k) {
	// 반시계 방향 회전일경우 시계방향으로 바꾼다.
	if (d == 1)
		k = m - k;
	// x의 배수인 원판을 회전시킨다.
	for (int i = x - 1; i < n; i += x) {	// 0-base
		ranges::rotate(board[i], board[i].end() - k);
	}

	//cout << "회전후 회전판:\n";
	//Print();
}

bool Remove() {
	// 삭제할 위치들을 찾는다.
	vector<pair<int, int>> removeList;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == INF)
				continue;

			for (int k = 0; k < 4; ++k) {
				int ni = i + di[k];
				int nj = (j + dj[k] + m) % m;
				if (IsInside(ni, nj) && board[i][j] == board[ni][nj]) {
					removeList.emplace_back(ni, nj);
					removeList.emplace_back(i, j);
				}
			}
		}
	}

	for (auto [i, j] : removeList) {
		board[i][j] = INF;
	}

	//cout << "삭제후 회전판:\n";
	//Print();

	return !removeList.empty();
}

void Modify() {
	int count = 0;
	double avg = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == INF)
				continue;
			avg += board[i][j];
			++count;
		}
	}
	avg /= count;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == INF)
				continue;
			if(avg < board[i][j])
				board[i][j] -= 1;
			else if (board[i][j] < avg)
				board[i][j] += 1;
		}
	}

	//cout << "수정후 회전판:\n";
	//Print();
}

bool IsInside(int i, int j) {
	return 0 <= i && i < n && 0 <= j && j < m;
}

void Print() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == INF)
				cout << "x ";
			else
				cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}
