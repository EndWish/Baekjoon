#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <algorithm>
#include <ranges>
#include <functional>
//#include <format>	c++ latest

#define pii pair<int,int>

using namespace std;

int dr[] = { 1, -1, 0,0 };
int dc[] = { 0, 0, 1,-1 };

int t;
int h, w;
array<array<char, 100>, 100> board;
array<array<bool, 100>, 100> visit;
array<vector<pii>, 26> door;
array<bool, 26> haveKey;

bool Inside(int r, int c);
void Run(int r, int c, queue<pii>& q, int& ans, vector<pii>& stopped);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> t;
	while (t-- > 0) {
		//최기화,입력값 받기

		// 1. 초기화
		for (auto& v : visit)
			v.fill(false);
		for (auto& d : door)
			d.clear();
		haveKey.fill(false);

		// 2. 보드 입력받기
		cin >> h >> w;
		for (int r = 0; r < h; ++r) {
			for (int c = 0; c < w; ++c) {
				cin >> board[r][c];
				if (isupper(board[r][c]))
					door[board[r][c] - 'A'].emplace_back(r, c);	// 문의 위치들을 저장
			}
		}

		// 3. 키 입력받기
		string inputKey;
		cin >> inputKey;
		if(inputKey != "0")
			for(char c : inputKey)
				haveKey[c - 'a'] = true;

		// 4. 가진 키의 문들을 제거
		for (int i = 0; i < 26; ++i)
			if (haveKey[i])
				for (auto [r, c] : door[i])
					board[r][c] = '.';

		//문제해결

		
		int ans = 0;
		queue<pii> q;
		vector<pii> stopped;

		// 1. 가장 자리에서 출발할 수 있는 지점들 삽입	[수정 : 문이나 열쇠일 경우도 할 수 있도록]
		for (int c = 0; c < w; ++c) {

			Run(0, c, q, ans, stopped);	// 위
			Run(h - 1, c, q, ans, stopped);	// 아래
		}
		for (int r = 1; r < h - 1; ++r) {
			Run(r, 0, q, ans, stopped);// 왼쪽
			Run(r, w - 1, q, ans, stopped);// 오른쪽
		}

		// 2. 큐가 빌때 까지 BFS수행
		while (!q.empty()) {
			auto[r,c] = q.front();
			q.pop();

			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (!Inside(nr, nc) || board[nr][nc] == '*' || visit[nr][nc])
					continue;

				Run(nr, nc, q, ans, stopped);
			}
		}

		//출력
		cout << ans << "\n";

	}


}

bool Inside(int r, int c) 
{
	if (r < 0 || h <= r || c < 0 || w <= c)
		return false;
	return true;
}

void Run(int r, int c, queue<pii>& q, int& ans, vector<pii>& stopped )
{
	visit[r][c] = true;

	//if(board[r][c] != '*')
	//	cout << format("({0},{1}) : ", r, c);	// [임시]

	if (board[r][c] == '.') {	// 빈공간
		q.emplace(r, c);
		//cout << format(" 빈공간\n");	// [임시]
	}
	else if (board[r][c] == '$') {	// 문서
		q.emplace(r, c);
		++ans;
		//cout << format(" 문서 : 결과+1\n");	// [임시]
	}
	else if (isupper(board[r][c])) {	// 문
		stopped.emplace_back(r, c);
		//cout << format(" 막힌문 {0}\n", board[r][c]);	// [임시]
	}
	else if (islower(board[r][c])) {	// 키
		q.emplace(r, c);
		char keyNumber = board[r][c] - 'a';
		if (!haveKey[keyNumber]) {	// 가지고 있었던 키가 아닐 경우
			//cout << format(" {}키, ", board[r][c]);	// [임시]
			haveKey[keyNumber] = true;

			for (auto [stoppedR, stoppedC] : stopped) {	// 키가 없어서 멈춰섰던 곳에서 다시 진행하도록 큐에 삽입
				//cout << format("({0},{1})", stoppedR, stoppedC);	// [임시]
				if (board[stoppedR][stoppedC] - 'A' == keyNumber) {
					q.emplace(stoppedR, stoppedC);
					//cout << format("=open");	// [임시]
				}
				//cout << format(", ");	// [임시]
			}	

			auto p = ranges::remove_if(stopped, [keyNumber](const pii s) {	// 다시 시작하는 위치들을 stopped에서 제거
				if (board[s.first][s.second] - 'A' == keyNumber)
					return true;
				return false;
				});
			stopped.erase(p.begin(), p.end());

			for (auto [doorR, doorC] : door[keyNumber])	// 주운 키로 열수 있는 방문들을 제거
				board[doorR][doorC] = '.';
		}
		//cout << format("\n");	// [임시]
	}
}
