#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 10

using namespace std;

int n;
int board[MAXN][MAXN];
int visitBackSlash[MAXN + MAXN - 1];
int visitSlash[MAXN + MAXN - 1];
vector<pair<int, int>> whiteBlanks, blackBlanks;
int dfsAns;

void DFS(vector<pair<int, int>>& blanks, int index, int num);
int BackSlashIndex(int x, int y);
int SlashIndex(int x, int y);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			cin >> board[x][y];
			if (board[x][y] == 1) {
				if ((x + y) & 1)	// x+y가 홀수일 경우 검정타일
					blackBlanks.emplace_back(x, y);
				else	// x+y가 짝수일 경우 흰타일
					whiteBlanks.emplace_back(x, y);
			}
				
		}
	}

	//문제해결
	int res = 0;

	dfsAns = 0;
	DFS(blackBlanks, 0, 0);
	res += dfsAns;

	dfsAns = 0;
	DFS(whiteBlanks, 0, 0);
	res += dfsAns;

	//출력
	cout << res;

}

void DFS(vector<pair<int, int>>& blanks, int index, int num) {
	if (num + (blanks.size() - index) <= dfsAns)
		return;

	if (index == blanks.size()) {
		dfsAns = max(dfsAns, num);
		//cout << num << "\n";
		return;
	}

	// 안 놓을 경우
	DFS(blanks, index + 1, num);

	// 놓을 경우
	auto [x, y] = blanks[index];
	int backSlashIndex = BackSlashIndex(x, y);
	int slashIndex = SlashIndex(x, y);
	if (visitBackSlash[backSlashIndex] == 0 && visitSlash[slashIndex] == 0) {
		++visitBackSlash[backSlashIndex];
		++visitSlash[slashIndex];
		DFS(blanks, index + 1, num + 1);

		--visitBackSlash[backSlashIndex];
		--visitSlash[slashIndex];
	}

}

int BackSlashIndex(int x, int y) {
	int z = x - y;
	if (0 <= z)
		return z;
	else
		return (MAXN - 1) - z;
}
int SlashIndex(int x, int y) {
	return x + y;
}