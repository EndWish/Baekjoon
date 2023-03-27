#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>


using namespace std;

#define MAXN 4001

string s1, s2;
array<array<int, MAXN>, MAXN> dp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> s1 >> s2;
	s1.insert(s1.begin(), '0');
	s2.insert(s2.begin(), '0');
	
	int ans = 0;
	for (int i = 1; i < s1.size(); ++i) {
		for (int j = 1; j < s2.size(); ++j) {
			if (s1[i] == s2[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
				ans = max(ans, dp[i][j]);
			}
				
		}
	}

	cout << ans;

}

