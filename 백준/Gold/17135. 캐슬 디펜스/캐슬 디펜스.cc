#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 15
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

int n, m, d;
int InitBoard[MAXN][MAXN];
int board[MAXN][MAXN];
bool archer[MAXN];

vector<pii> atk;

bool Inside(int r, int c);
int DFS(int index, int archerNum);
int Simulation();
void Print();

int cnt;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> d;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			cin >> InitBoard[r][c];

	//문제해결
	cout << DFS(0, 0);

	//출력

}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}

int DFS(int index, int archerNum) {
	if (archerNum == 3) {
		// 시뮬레이션 수행
		return Simulation();
	}

	if (m <= index)	// 아처를 3명 배치하지 않은 경우
		return -1;

	int result = 0;
	// 아처를 배치하는 경우
	archer[index] = true;
	result = max(result, DFS(index + 1, archerNum + 1));
	// 아처를 배치하지 않는 경우
	archer[index] = false;
	result = max(result, DFS(index + 1, archerNum));
	return result;
}

int Simulation() {
	// 보드를 초기화 한다.
	copy_n(&InitBoard[0][0], MAXN * MAXN, &board[0][0]);
	int result = 0;

	// n번 혹은 보드에 적이 없을때 까지 반복한다.
	//Print();
	for (int i = 0; i < n; ++i) {
		
		// 아처는 적을 공격한다.
		atk.clear();
		for (int archerIndex = 0; archerIndex < m; ++archerIndex) {
			if (archer[archerIndex]) {	// archerIndex 위치에 아처가 있을 경우
				int ar = n, ac = archerIndex;	// 아처의 위치
				// 공격범위를 확인한다.
				int minDist = INF;
				int tr, tc;
				for (int r = max(0, ar - d); r < n; ++r) {
					for (int c = max(0, ac - d); c < min(m, ac + d + 1); ++c) {
						int dist = abs(r - ar) + abs(c - ac);
						if (!Inside(r, c) || board[r][c] == 0 || d < dist) {
							continue;
						}
							
						if (dist < minDist || (dist == minDist && c < tc)) {
							minDist = dist;
							tr = r;
							tc = c;
						}
					}
				}
				if(minDist != INF)
					atk.emplace_back(tr, tc);
			}
		}
		// 공격당한 적은 삭제된다. (result + 1)
		for (auto [r, c] : atk) {
			if (board[r][c] == 1) {
				board[r][c] = 0;
				++result;
			}
		}
		//Print();
		// 적은 이동한다.
		for (int r = n - 1; r >= i; --r) {
			for (int c = 0; c < m; ++c) {
				if (board[r][c] == 1) {
					board[r][c] = 0;
					if(r + 1 < n)
						board[r + 1][c] = 1;
				}
			}
		}
		//Print();
	}

	return result;
}

//void Print() {
//	cout << "\n";
//	for (int r = 0; r < n; ++r) {
//		for (int c = 0; c < m; ++c) {
//			cout << board[r][c] << " ";
//		}
//		cout << "\n";
//	}
//}
