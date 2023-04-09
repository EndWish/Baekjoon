#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

ll x, y, w, s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> x >> y >> w >> s;
	ll diagonal = min(x, y);
	ll Straight = x + y - diagonal * 2;

	ll ans = min(Straight * w, Straight / 2 * s * 2 + Straight % 2 * w)	// 직선방향으로 가는 최단 거리
			+ min(diagonal * s, diagonal * 2 * w);	// 대각선으로 가는 최단 거리
	cout << ans;
}
