#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pii pair<ll,ll>

int cnt;
int n, input;
array<array<int, 999>, 999> board;

pii func(int sr, int sc, int wid);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> input;
	
	int halfN = n / 2;
	int r = halfN, c = halfN;
	board[r][c] = ++cnt;
	for (int i = 3; i <= n; i += 2) {
		tie(r, c) = func(r, c, i);
	}

	pii pos;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cout << board[r][c] << " ";
			if (board[r][c] == input) {
				pos = { r, c };
			}
		}
		cout << "\n";
	}
	cout << pos.first + 1 << " " << pos.second + 1;
}

pii func(int sr, int sc, int wid) {
	int r = sr - 1, c = sc;
	board[r][c] = ++cnt;
	// 위쪽
	for (int i = 0; i < wid - 2; ++i) {
		board[r][++c] = ++cnt;
	}
	// 오른쪽
	for (int i = 0; i < wid - 1; ++i) {
		board[++r][c] = ++cnt;
	}
	// 아래
	for (int i = 0; i < wid - 1; ++i) {
		board[r][--c] = ++cnt;
	}
	// 왼쪽
	for (int i = 0; i < wid - 1; ++i) {
		board[--r][c] = ++cnt;
	}
	return { r, c };
}
