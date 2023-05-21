#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define MAXN 1'000'001

array<ll, MAXN> f, g;
ll t, n;

void InitF();
void InitG();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	InitF();
	InitG();

	cin >> t;
	while (t--) {
		cin >> n;
		cout << g[n] << "\n";
	}
	
}

void InitF() {
	for (ll i = 1; i < MAXN; ++i) {
		for (ll j = i; j < MAXN; j += i) {
			f[j] += i;
		}
	}
}

void InitG() {
	for (ll i = 1; i < MAXN; ++i) {
		g[i] = g[i - 1] + f[i];
	}
}
