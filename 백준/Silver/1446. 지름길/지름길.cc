#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

struct Load {
	int s, e, d;
};

int n, d;
vector<Load> loads;
vector<int> dp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> d;
	dp.assign(d + 1, {});
	loads.assign(n, {});
	for (Load& load : loads) {
		cin >> load.s >> load.e >> load.d;
	}
	ranges::sort(loads, greater<int>{}, & Load::e);

	//문제해결
	dp[0] = 0;
	for (int i = 1; i <= d; ++i) {
		dp[i] = dp[i - 1] + 1;
		while (!loads.empty()) {
			Load load = loads.back();
			if (load.e == i) {
				dp[i] = min(dp[i], dp[load.s] + load.d);
				loads.pop_back();
			}
			else {
				break;
			}
		}
	}

	//출력
	cout << dp[d];

}
