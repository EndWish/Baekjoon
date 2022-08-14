#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>
//#include <format>

#define pii pair<int,int>

using namespace std;

int t;
int n, m;
vector<pii> range;

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> n >> m;
		range.assign(m, {});
		for (auto& [s, e] : range)
			cin >> s >> e;

		//문제해결
		ranges::sort(range, [](pii a, pii b) {
			if (a.second == b.second)
				return a.first < b.first;
			return a.second < b.second;
			});

		int ans = 0;
		vector<bool> book(n + 1, true);

		for (auto [s, e] : range) {
			for (int i = s; i <= e; ++i) {
				if (book[i]) {
					book[i] = false;
					++ans;
					break;
				}
			}
		}

		//출력
		cout << ans << "\n";

	}


}