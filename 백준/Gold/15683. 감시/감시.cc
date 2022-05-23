#include <iostream>
#include <memory.h>
#include <array>
#include <vector>

#define MAXN 8

using namespace std;

class CCTV {
public:
	int r, c;
	int type;
	int dir = 0;

	CCTV(int r, int c, int type) : r{ r }, c{ c }, type{ type }{};
	int SetSight() const;
	int SetSightOneDir(int direction) const;

};

int n, m;
array<array<int, MAXN>, MAXN> board;
array<array<bool, MAXN>, MAXN> visit;
vector<CCTV> cctvs;
int blindSpot = 64;
int space = 0;

bool Inside(int r, int c);
void DFS(vector<CCTV>::iterator it);
int GetBlindSpot();

void PrintBoard();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cctvs.reserve(8);

	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> board[i][j];
			if (0 == board[i][j]) {
				++space;
			}
			else if (1 <= board[i][j] && board[i][j] <= 5) {
				cctvs.emplace_back(i, j, board[i][j]);
			}
		}
	}

	//문제해결
	DFS(cctvs.begin());
	
	//출력
	cout << blindSpot;

}

int CCTV::SetSightOneDir(int direction) const {
	int result = 0;

	int nr = r, nc = c;

	int dr, dc;
	switch (direction) {
	case 0: dr = 1, dc = 0; break;
	case 1: dr = 0, dc = -1; break;
	case 2: dr = -1, dc = 0; break;
	case 3: dr = 0, dc = 1; break;
	default: break;
	}

	while (Inside(nr, nc)) {
		if (board[nr][nc] == 6)
			break;

		if (board[nr][nc] == 0 && !visit[nr][nc]) {
			visit[nr][nc] = true;
			++result;
		}

		nr += dr;
		nc += dc;
	}

	return result;
}

int CCTV::SetSight() const {
	switch (type) {
	case 1: return SetSightOneDir(dir);
	case 2: return SetSightOneDir(dir) + SetSightOneDir((dir + 2) % 4);
	case 3: return SetSightOneDir(dir) + SetSightOneDir((dir + 1) % 4);
	case 4: return SetSightOneDir(dir) + SetSightOneDir((dir + 1) % 4) + SetSightOneDir((dir + 2) % 4);
	case 5: return SetSightOneDir(dir) + SetSightOneDir((dir + 1) % 4) + SetSightOneDir((dir + 2) % 4) + SetSightOneDir((dir + 3) % 4);
	default: return 0;
	}
}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}

int GetBlindSpot() {
	//visit 리셋
	memset(&visit[0][0], false, sizeof(visit));

	//시야 표시
	int sightSpot = 0;
	for (const CCTV& cctv : cctvs)
		sightSpot += cctv.SetSight();

	return space - sightSpot;
}

void DFS(vector<CCTV>::iterator it) {

	if (it == cctvs.end()) {
		blindSpot = std::min(blindSpot, GetBlindSpot());
		return;
	}

	for (int i = 0; i < 4; ++i) {
		it->dir = i;
		DFS(it + 1);
	}

}

void PrintBoard() {
	cout << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}

}
