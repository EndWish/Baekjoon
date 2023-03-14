#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define MAXN 100
#define pii pair<int,int>

int gr, gc, k;
int t;
array<array<int, MAXN>, MAXN> board;
int n, m;

void RCalculation();
void CCalculation();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> gr >> gc >> k;
	--gr; --gc;
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			cin >> board[r][c];
		}
	}
	
	//문제해결
	n = 3; m = 3;
	while (true) {
		// 원하는 숫자가 되었는지 확인한다.
		if (100 < t) {
			break;
		}
		if (board[gr][gc] == k) {
			break;
		}

		// R,C연산을 수행한다.
		if (n >= m)
			RCalculation();
		else
			CCalculation();

		++t;
	}

	if (100 < t)
		cout << -1;
	else
		cout << t;

}
void RCalculation() {
	int newM = 0;
	for (int r = 0; r < n; ++r) {
		// 한 행개수들을 저장한다.
		unordered_map<int, int> numCountMap;
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 0)
				continue;
			++numCountMap[board[r][c]];
			board[r][c] = 0;
		}

		// 수와 등장횟수를 정렬한다. (벡터에는 num과 cnt가 반대로 되어있다.)
		vector<pii> nNumVec;
		for (auto [num, cnt] : numCountMap)
			nNumVec.emplace_back(cnt, num);
		ranges::sort(nNumVec);

		// 새로이 저장한다.
		for (int i = 0; auto [cnt, num] : nNumVec) {
			if (100 <= i)
				break;
			board[r][i++] = num;
			board[r][i++] = cnt;
		}
		newM = max(newM, min(100, (int)nNumVec.size() * 2));
	}
	m = newM;
}
void CCalculation() {
	int newN = 0;
	for (int c = 0; c < m; ++c) {
		// 한 행개수들을 저장한다.
		unordered_map<int, int> numCountMap;
		for (int r = 0; r < n; ++r) {
			if (board[r][c] == 0)
				continue;
			++numCountMap[board[r][c]];
			board[r][c] = 0;
		}

		// 수와 등장횟수를 정렬한다. (벡터에는 num과 cnt가 반대로 되어있다.)
		vector<pii> nNumVec;
		for (auto [num, cnt] : numCountMap)
			nNumVec.emplace_back(cnt, num);
		ranges::sort(nNumVec);

		// 새로이 저장한다.
		for (int i = 0; auto [cnt, num] : nNumVec) {
			if (100 <= i)
				break;
			board[i++][c] = num;
			board[i++][c] = cnt;
		}
		newN = max(newN, min(100, (int)nNumVec.size() * 2));
	}
	n = newN;
}
