#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define MAXN 101
#define MOD 1000000007LL

int n, l, r;
array<array<array<ll, MAXN>, MAXN>, MAXN> dp;

ll GetDP(int h, int l, int r);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ranges::fill_n(&dp[0][0][0], MAXN * MAXN * MAXN, -1);

	cin >> n >> l >> r;
	
	cout << GetDP(n, l, r);

}

ll GetDP(int h, int l, int r) {

	if (dp[h][l][r] != -1)
		return dp[h][l][r];

	if (h == 1 && l == 1 && r == 1)
		return dp[h][l][r] = 1;

	if(h < 1 || l < 1 || r < 1 || l + r > h + 1)
		return dp[h][l][r] = 0;

	dp[h][l][r] = GetDP(h - 1, l - 1, r) + GetDP(h - 1, l, r - 1) + GetDP(h - 1, l, r) * (h - 2);
	dp[h][l][r] %= MOD;

	return dp[h][l][r];
}
