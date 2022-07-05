#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

#define ll long long

using namespace std;

ll t;
int n, m;
vector<ll> sumsA, sumsB;

void Input(int num, vector<ll>& sums);
void MakeCombi(vector<ll>& sums, vector<ll>& dest);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> t;

	cin >> n;
	Input(n, sumsA);

	cin >> m;
	Input(m, sumsB);

	//문제해결
	vector<ll> CombiA, CombiB;
	MakeCombi(sumsA, CombiA);
	MakeCombi(sumsB, CombiB);
	ranges::sort(CombiB);

	ll ans = 0;
	for (ll a : CombiA) {
		auto [b, e] = ranges::equal_range(CombiB, t - a);
		ans += distance(b, e);
	}

	//출력
	cout << ans;

}

void Input(int num, vector<ll>& sums)
{
	sums.assign(num, 0);
	cin >> sums[0];
	for (int i = 1; i < num; ++i) {
		cin >> sums[i];
		sums[i] += sums[i - 1];
	}
}

void MakeCombi(vector<ll>& sums, vector<ll>& dest) 
{
	dest.reserve(sums.size() * sums.size());
	for (ll v : sums)
		dest.push_back(v);

	for (int i = 0; i < sums.size(); ++i)
		for (int j = i + 1; j < sums.size(); ++j)
			dest.push_back(sums[j] - sums[i]);
}
