#include <iostream>
#include <memory.h>

#define ll long long
#define DIV 1'000'000'000

using namespace std;

int n;
int dp[2][10][10][10];	// dp[이전-이후][a][b][e] : 숫자를 a~b를 포함하고 e로 끝나는 수의 개수

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	if (n < 10) {
		cout << 0;
		return 0;
	}

	for (int i = 1; i <= 9; ++i)
		dp[0][i][i][i] = 1;

	//문제해결
	for (int len = 1; len < n; ++len) {
		memset(&dp[1], 0, sizeof(int) * 10 * 10 * 10);
		for (int a = 0; a < 10; ++a) {
			for (int b = a; b < 10; ++b) {
				for (int e = a; e <= b; ++e) {
					int ne[] = { e + 1, e - 1 };
					for (int i = 0; i < 2; ++i) {
						if (ne[i] < 0 || 9 < ne[i])
							continue;

						if (a <= ne[i] && ne[i] <= b) {
							dp[1][a][b][ne[i]] += dp[0][a][b][e];
							dp[1][a][b][ne[i]] %= DIV;
						}
						else {
							if (ne[i] < a) {
								dp[1][ne[i]][b][ne[i]] += dp[0][a][b][e];
								dp[1][ne[i]][b][ne[i]] %= DIV;
							}
							else if (b < ne[i]) {
								dp[1][a][ne[i]][ne[i]] += dp[0][a][b][e];
								dp[1][a][ne[i]][ne[i]] %= DIV;
							}
						}
					}
				}
			}
		}

		memcpy(&dp[0], &dp[1], sizeof(int) * 10 * 10 * 10);
	}

	//출력
	ll ans = 0;
	for (int e = 0; e < 10; ++e)
		ans = (ans + dp[1][0][9][e]) % DIV;

	cout << ans;
}
