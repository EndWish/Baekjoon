#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

#define ll long long

using namespace std;

int n;
vector<ll> v;
ll minValue = numeric_limits<int>::max();
pair<int, int> ans;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	v.assign(n, 0);
	for (ll& i : v)
		cin >> i;

	//문제해결
	int s = 0, e = n - 1;
	while (s < e) {
		ll value = v[s] + v[e];

		if (abs(value) < minValue) {
			minValue = abs(value);
			ans = { v[s], v[e] };
		}

		if (0 < value)
			--e;
		else if (value < 0)
			++s;
		else
			break;
	}

	if (ans.first > ans.second)
		swap(ans.first, ans.second);
	
	//출력
	cout << ans.first << " " << ans.second;

}