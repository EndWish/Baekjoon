#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n, d;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> d;

	//문제해결
	multiset<ll> mset;
	queue<ll> q;
	mset.insert(0);

	ll ans = numeric_limits<ll>::min();
	for (int i = 0; i < n; ++i) {
		ll num;
		cin >> num;

		ll dp = *mset.rbegin() + num;
		//cout << "index : " << i << " , dp : " << dp << "\n";
		ans = max(ans, dp);

		mset.insert(dp);
		q.push(dp);

		if (d < q.size()) {
			mset.erase(mset.find(q.front()));
			q.pop();
		}
	}

	cout << ans;

}

