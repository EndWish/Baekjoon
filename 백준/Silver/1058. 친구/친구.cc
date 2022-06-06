#include <iostream>
#include <array>
#include <algorithm>
#include <ranges>

#define MAXN 50

using namespace std;

int n;

array<array<char, MAXN>, MAXN> board;
array<array<bool, MAXN>, MAXN> fri2;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> board[i][j];

	//문제해결
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {

			if (board[i][j] == 'Y') { // i와 j가 친구일 경우
				fri2[i][j] = true;	// j는 i의 2-친구
				fri2[j][i] = true;	// i는 j의 2-친구

				for (int k = 0; k < n; ++k) {
					if (board[j][k] == 'Y' && i != k)
						fri2[i][k] = true;	// 친구의 친구인 k 는 2-친구이다.
					if (board[i][k] == 'Y' && k != j)
						fri2[j][k] = true;	// 친구의 친구인 k 는 2-친구이다.
				}

			}


		}
	}

	//출력
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans = ranges::max(ans, (int)ranges::count(fri2[i].begin(), fri2[i].begin() + n, true));
	}

	cout << ans;

}