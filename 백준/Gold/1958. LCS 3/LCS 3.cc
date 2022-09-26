#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ranges>
#include <algorithm>
//#include <numeric>
//#include <format>

using namespace std;

#define MAXN 101

string s[3];
int dp[MAXN][MAXN][MAXN];

int LCM(const string& s1, const string& s2, const string& s3);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> s[0] >> s[1] >> s[2];

	//문제해결

	//출력
	cout << LCM(s[0], s[1], s[2]);

}

int LCM(const string& s1, const string& s2, const string& s3) {

	for (int i = 1; i <= s1.length(); ++i) {
		for (int j = 1; j <= s2.length(); ++j) {
			for (int k = 1; k <= s3.length(); ++k) {
				if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
					dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
				}
				else {
					dp[i][j][k] = max({ dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1] });
				}
			}
		}
	}
	
	return dp[s1.length()][s2.length()][s3.length()];
}
