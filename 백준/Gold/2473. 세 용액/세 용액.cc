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

	vector<tuple<ll, int, int>> v2;	// 두용액의 조합
	v2.reserve(n * n / 2);
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			v2.emplace_back(v[i] + v[j], i, j);

	//문제해결
	ll ansMin = numeric_limits<ll>::max();
	array<ll, 3> ansValue;
	for (auto [value, index1, index2] : v2) {
		int right = distance(v.begin(), lower_bound(v.begin(), v.end(), -value));
		int left = right - 1;

		while (right == index1 || right == index2) {
			++right;
		}
		while (left == index1 || left == index2) {
			--left;
		}

		ll rightValue = right < n ? value + v[right] : numeric_limits<ll>::max();
		if (abs(rightValue) < ansMin) {
			ansMin = abs(rightValue);
			ansValue = { v[index1], v[index2], v[right] };
		}

		ll leftValue = 0 <= left ? value + v[left] : numeric_limits<ll>::max();
		if (abs(leftValue) < ansMin) {
			ansMin = abs(leftValue);
			ansValue = { v[index1], v[index2], v[left] };
		}
	}
	
	//출력
	sort(ansValue.begin(), ansValue.end());
	for (ll i : ansValue)
		cout << i << " ";

}