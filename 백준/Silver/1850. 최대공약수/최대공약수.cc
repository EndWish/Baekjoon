#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define ll long long

ll a, b;

ll GCD(ll a, ll b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> a >> b;

	//문제해결
	ll gcd = GCD(a, b);

	//출력
	for (ll i = 0; i < gcd; ++i) {
		cout << 1;
	}

}

ll GCD(ll a, ll b) {
	if (a < b)
		swap(a, b);
	if (b == 0)
		return a;
	return GCD(b, a % b);
}
