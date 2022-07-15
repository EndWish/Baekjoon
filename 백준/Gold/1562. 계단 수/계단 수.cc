#include <iostream>

#define ll long long
#define DIV 1'000'000'000

using namespace std;

int n;
ll dp[101][10][10][10];	// dp[len][a][b][e] : 길이가 len이고 숫자를 a~b를 포함하고 e로 끝나는 수의 개수

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	if (n < 10) {
		cout << 0;
		return 0;
	}

	for (int i = 1; i <= 9; ++i)
		dp[1][i][i][i] = 1;

	//문제해결
	for (int len = 1; len < n; ++len) {
		for (int a = 0; a < 10; ++a) {
			for (int b = a; b < 10; ++b) {
				for (int e = a; e <= b; ++e) {
					int ne[] = { e + 1, e - 1 };
					for (int i = 0; i < 2; ++i) {
						if (ne[i] < 0 || 9 < ne[i])
							continue;

						if (a <= ne[i] && ne[i] <= b) {
							dp[len + 1][a][b][ne[i]] += dp[len][a][b][e];
							dp[len + 1][a][b][ne[i]] %= DIV;
						}
						else {
							if (ne[i] < a) {
								dp[len + 1][ne[i]][b][ne[i]] += dp[len][a][b][e];
								dp[len + 1][ne[i]][b][ne[i]] %= DIV;
							}
							else if (b < ne[i]) {
								dp[len + 1][a][ne[i]][ne[i]] += dp[len][a][b][e];
								dp[len + 1][a][ne[i]][ne[i]] %= DIV;
							}
						}
					}
				}
			}
		}
	}

	//출력
	ll ans = 0;
	for (int e = 0; e < 10; ++e)
		ans = (ans + dp[n][0][9][e]) % DIV;

	cout << ans;
}
