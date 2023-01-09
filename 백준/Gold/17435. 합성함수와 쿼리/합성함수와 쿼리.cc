#include <iostream>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXM 200'001
#define MAXE 24

int m, q;
array<array<int, MAXM>, MAXE> f;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> m;
	for (int i = 1; i <= m; ++i)
		cin >> f[0][i];

	//문제해결
	for (int e = 1; e < MAXE; ++e) {
		for (int x = 1; x <= m; ++x) {
			f[e][x] = f[e - 1][f[e - 1][x]];
		}
	}

	cin >> q;
	for (int i = 0; i < q; ++i) {
		int n, x;
		cin >> n >> x;

		for (int e = MAXE - 1; e >= 0; --e) {
			if ((1 << e) <= n) {
				x = f[e][x];
				n -= (1 << e);
			}
		}
		//cout << "결과 : ";
		cout << x << "\n";
	}


	//출력

}
