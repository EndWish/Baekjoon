#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n;
vector<ll> heights;
vector<int> sights;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	heights.assign(n, {});
	sights.assign(n, {});
	for (ll& height : heights)
		cin >> height;

	//문제해결
	for (int i = 0; i < heights.size(); ++i) {
		ll height1 = heights[i];
		double maxLean = numeric_limits<double>::lowest();
		ll maxHeight = 0;
		for (int j = i + 1; j < heights.size(); ++j) {
			ll height2 = heights[j];

			double lean = (double)(height2 - height1) / (j - i);
			if (maxLean < lean) {
				++sights[i];
				++sights[j];
				maxLean = lean;
			}
		}
	}

	cout << *ranges::max_element(sights);

}
