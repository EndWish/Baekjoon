#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>
//#include <format>

#define ll long long
#define NUM 1'000'000'000LL

using namespace std;

int n, m;

vector<ll> mul;
vector<ll> ans;

ll GCD(ll a, ll b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	if (m > n - m) {
		m = n - m;
	}
	
	//문제해결
	for (int i = n; i > n - m; --i) {
		mul.push_back(i);
	}
	for (int i = 2; i <= m; ++i) {
		int div = i;
		for (int j = 0; j < mul.size(); ++j) {
			int gcd = GCD(mul[j], div);
			div /= gcd;
			mul[j] /= gcd;
			if (div == 1) {
				break;
			}
		}
	}

	ans.push_back(1);
	for (int i = 0; i < mul.size(); ++i) {

		for (int j = 0; j < ans.size(); ++j) {
			ans[j] *= mul[i];
		}
		
		for (int j = 0; j < ans.size(); ++j) {
			if (NUM <= ans[j]) {
				if (j + 1 < ans.size()) {
					ans[j + 1] += ans[j] / NUM;
				}
				else {
					ans.push_back(ans[j] / NUM);
				}
				ans[j] %= NUM;
			}
			else {
				break;
			}
		}


	}

	//출력
	for (int i = ans.size() - 1; i >= 0; --i) {
		if (i != ans.size() - 1) {
			int digit = (log10(NUM)) - log10(ans[i]);
			for (int j = 0; j < digit; ++j) {
				cout << "0";
			}
		}
		cout << ans[i];
	}

}

ll GCD(ll a, ll b) {
	if (a < b)
		swap(a, b);

	if (b == 0)
		return a;
	return GCD(b, a % b);
}
