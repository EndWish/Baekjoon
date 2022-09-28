#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
//#include <numeric>
//#include <format>

using namespace std;

int n;
bool board[100][100];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			cin >> board[x][y];
		}
	}

	//문제해결
	for (int via = 0; via < n; ++via) {
		for (int s = 0; s < n; ++s) {
			for (int e = 0; e < n; ++e) {
				if (board[s][via] && board[via][e])
					board[s][e] = true;
			}
		}
	}

	//출력
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			cout << board[x][y] << " ";
		}
		cout << "\n";
	}

}
