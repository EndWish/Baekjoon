#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>
//#include <format>

#define ll long long

using namespace std;

int n, m;
vector<vector<char>> board;

int IsPowed(int num);
bool IsInside(int r, int c);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	board.assign(n, vector<char>(m, 0));
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			board[r][c] -= '0';
		}
	}

	//문제해결
	int result = -1;
	for (int sr = 0; sr < n; ++sr) {
		for (int sc = 0; sc < m; ++sc) {

			for (int nr = 0; nr < n; ++nr) {
				for (int nc = 0; nc < m; ++nc) {

					//cout << format("({},{}) ({},{})\n", sr, sc, nr, nc);

					int dr = nr - sr;
					int dc = nc - sc;

					int num = board[sr][sc];
					result = max(result, IsPowed(num));
					if (dr == 0 && dc == 0) {
						continue;
					}

					int ar = sr;
					int ac = sc;
					while (true) {
						ar += dr;
						ac += dc;
						if (!IsInside(ar, ac))
							break;
						num = num * 10 + board[ar][ac];
						if (num <= result)
							continue;
						result = max(result, IsPowed(num));
					}
				}
			}

		}
	}

	//출력
	cout << result;
}

bool IsInside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}

int IsPowed(int num) {
	int q = sqrt(num);
	if (q * q == num)
		return num;
	return -1;
}
