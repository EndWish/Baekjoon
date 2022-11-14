#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>

using namespace std;

#define ll long long

int g;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//초기화,입력값 받기
	cin >> g;

	//문제해결
	vector<ll> nums;
	ll num = 1;
	while ( (num - 1)*(num - 1) >= num * num - g) {
		nums.push_back(num * num);
		++num;
	}

	vector<int> ans;
	ll curWeight = 2;
	while ((curWeight - 1) * (curWeight - 1) >= curWeight * curWeight - g) {
		ll sqrPreWeight = curWeight * curWeight - g;
		if (ranges::binary_search(nums, sqrPreWeight))
			ans.push_back(curWeight);
		++curWeight;
	}

	//출력
	if (ans.empty()) {
		cout << -1;
	}
	else {
		for (int value : ans)
			cout << value << "\n";
	}

}