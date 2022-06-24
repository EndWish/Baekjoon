#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>

// 23290

using namespace std;

bool Inside(int r, int c);

int fishDr[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int fishDc[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

int sharkDr[] = { -1, 0, 1, 0 };
int sharkDc[] = { 0, -1, 0, 1 };

class Board {
private:
	array<array<vector<int>, 4>, 4> fishes1, fishes2;
	array<array<vector<int>, 4>, 4>* pFishesBackBuffer = &fishes2;
	array<array<int, 4>, 4> smell;

public:
	array<array<vector<int>, 4>, 4>* pFishes = &fishes1;
	pair<int,int> shark;

private:
	bool IsSmell(int r, int c, int turn) {
		return smell[r][c] >= turn - 2;
	}
	bool IsShark(int r, int c) {
		return shark.first == r && shark.second == c;
	}

	void SharkDFS(int r, int c, const string& path, int eating, vector<pair<int, string>>& dest) {
		if (path.size() == 3) {
			dest.emplace_back(eating, path);
			return;
		}

		for (int i = 0; i < 4; ++i) {
			int nr = r + sharkDr[i];
			int nc = c + sharkDc[i];
			if (!Inside(nr, nc))
				continue;

			char ch = '1' + i;	// 이번에 이동하는 방향
			string nextPath = path + ch;

			int nextEating;
			if ((ch - path.back() == -2 || ch - path.back() == 2) && path.size() == 2)	// 왔는 위치로 돌아가며, 상어 시작 위치에 물고기가 겹처서 못먹었는 경우를 제외
				nextEating = eating;
			else
				nextEating = eating + (*pFishes)[nr][nc].size();
			
			SharkDFS(nr, nc, nextPath, nextEating, dest);
		}

	}

	void PrintBoard() {
		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				if ((*pFishes)[r][c].empty())
					cout << 'X';
				else
					cout << 'O';
			}
			cout << "\n";
		}
	}

public:
	Board() {
		fill_n(&smell[0][0], 16, -10);
	}

	// 2번
	void MoveFish(int turn) {
		//cout << "물고기이동!\n";	//임시 출력
		array<array<vector<int>, 4>, 4>& fishes = *pFishes;
		array<array<vector<int>, 4>, 4>& fishesNext = *pFishesBackBuffer;

		//PrintBoard();	// 임시 출력

		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				for (int fish : fishes[r][c]) {	// 모든 물고기들에 대해서

					bool moving = false;
					// 방향을 회전하면서 갈수 있는 곳이 있는지 확인한다.
					for (int i = 0; i < 8; ++i) {
						int nr = r + fishDr[fish];
						int nc = c + fishDc[fish];

						// 격자안 + 냄새x + 상어x = 갈수 있음
						if (Inside(nr, nc) && !IsSmell(nr, nc, turn) && !IsShark(nr, nc)) {
							fishesNext[nr][nc].push_back(fish);
							moving = true;
							break;
						}

						fish = fish - 1 >= 0 ? fish - 1 : 7;
					}

					if(!moving)	// 못 움직인 물고기
						fishesNext[r][c].push_back(fish);

				}
			}
		}

		swap(pFishes, pFishesBackBuffer);

		//PrintBoard();	// 임시 출력

	}
	// 3번
	void MoveShark(int turn) {
		//cout << "상어이동!\n";	// 임시 출력
		vector<pair<int, string>> paths;
		SharkDFS(shark.first, shark.second, ""s, 0, paths);	// 모든 경로들을 cmdsㅇ

		auto cmp = [](pair<int, string>& a, pair<int, string>& b) {	// 가장 많이 잡아먹을 수 있는 경올중 사전순으로 빠른것으로 정렬
			if (a.first == b.first)
				return a.second < b.second;
			return  a.first > b.first;
		};
		ranges::sort(paths, cmp);
		//cout << "DFS! : " << paths[0].first << " " << paths[0].second << "\n";	// 임시 출력

		for (char ch : paths[0].second) {
			shark.first += sharkDr[ch - '1'];
			shark.second += sharkDc[ch - '1'];
			if (!(*pFishes)[shark.first][shark.second].empty()) {
				smell[shark.first][shark.second] = turn;
				(*pFishes)[shark.first][shark.second].clear();
			}
		}

		//cout << "상어의 위치 : " << shark.first << " " << shark.second << "\n";;	// 임시 출력
	}
	// 4번 - 해결
	// 5번
	void CopyMagic() {
		//cout << "복사 마법!\n";	// 임시 출력
		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				ranges::copy((*pFishesBackBuffer)[r][c], back_inserter((*pFishes)[r][c]));
				(*pFishesBackBuffer)[r][c].clear();
			}
		}
		//PrintBoard();	// 임시 출력
	}

	// 결과 출력
	int GetFishesNum() {
		int fishesNum = 0;

		for (int r = 0; r < 4; ++r)
			for (int c = 0; c < 4; ++c)
				fishesNum += (*pFishes)[r][c].size();

		return fishesNum;
	}

};

int m, s;
Board board;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> m >> s;
	int inputR, inputC, inputDir;
	for (int i = 0; i < m; ++i) {
		cin >> inputR >> inputC >> inputDir;
		(*board.pFishes)[inputR - 1][inputC - 1].push_back(inputDir - 1);
	}
	cin >> inputR >> inputC;
	board.shark = { inputR - 1, inputC - 1 };

	//문제해결
	
	for (int turn = 0; turn < s; ++turn) {
		// 1. 5번에서 backBuffer에 있는 물고기들을 전면 버퍼에 복사하면 된다.
		// 2. 물고기들 이동
		board.MoveFish(turn);
		
		// 3. 상어 이동
		board.MoveShark(turn);
		
		// 4. 냄새 제거	- 3번에서 같이 처리됨
		// 5. 복사 마법
		board.CopyMagic();
		
	}

	//출력
	cout << board.GetFishesNum();
}

bool Inside(int r, int c) {
	if (r < 0 || 4 <= r || c < 0 || 4 <= c)
		return false;
	return true;
}