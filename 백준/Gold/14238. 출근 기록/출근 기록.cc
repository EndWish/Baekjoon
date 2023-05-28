#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

array<int, 3> alphabet;

bool visit[51][51][51][3][3];	// dp[a사용 개수][b사용 개수][c사용 개수][막지막에서 2번째 문자][마지막 문자];
char ans[50];

bool DFS(int a, int b, int c, int prev2, int prev1);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	string input;
	cin >> input;
	for (char ch : input)
		++alphabet[ch - 'A'];

	if (!DFS(0, 0, 0, 0, 0)) {
		cout << -1;
	}
	
}

bool DFS(int a, int b, int c, int prev2, int prev1) {
	if (a == alphabet[0] && b == alphabet[1] && c == alphabet[2])
		return true;

	if (visit[a][b][c][prev2][prev1])
		return false;
	visit[a][b][c][prev2][prev1] = true;

	if (1 <= alphabet[0] - a) {
		if (DFS(a + 1, b, c, prev1, 0)) {
			cout << 'A';
			return true;
		}
	}

	if (1 <= alphabet[1] - b && prev1 != 1) {
		if (DFS(a, b + 1, c, prev1, 1)) {
			cout << 'B';
			return true;
		}
	}

	if (1 <= alphabet[2] - c && prev1 != 2 && prev2 != 2) {
		if (DFS(a, b, c + 1, prev1, 2)) {
			cout << 'C';
			return true;
		}
	}

	return false;
}
