#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <cmath>

#define ll long long

using namespace std;

int n;
vector<ll> v;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	v.assign(n, 0);
	for (ll& i : v)
		cin >> i;

	sort(v.begin(), v.end());

	//문제해결
	tuple<ll, int, int, int> ans = { numeric_limits<ll>::max(), 0,0,0 };
	for (int l = 0; l < n - 2; ++l) {	// l번째 용액을 하나 선택하고 나머지 두 용액을 투포인터로 선택한다.
		int m = l + 1;
		int r = n - 1;

		while (m < r) {
			ll sum = v[l] + v[m] + v[r];
			if (abs(sum) < get<0>(ans))		// 절대값이 더 작으면 정답 갱신
				ans = { abs(sum), l, m, r };

			if (0 < sum)
				--r;
			else
				++m;

		}
	}
	
	//출력
	auto [value, index1, index2, index3] = ans;
	cout << v[index1] << " " << v[index2] << " " << v[index3];

}