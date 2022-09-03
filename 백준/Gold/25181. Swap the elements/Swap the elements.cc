#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int n;
vector<pair<int,int>> a;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		a.emplace_back(input, i);	// 수, 인덱스
	}
	ranges::sort(a);



	//문제해결
	int maxStraight = 1;
	int straight = 0;
	vector<int> matching(n);
	for (int i = 0; i < n; ++i) {
		matching[i] = a[i].first;

		if (i == 0 || matching[i - 1] != matching[i]) {
			straight = 1;
		}
		else {
			maxStraight = max(maxStraight, ++straight);
		}
	}

	ranges::rotate(matching, matching.begin() + maxStraight);

	bool success = true;
	for (int i = 0; i < n; ++i) {
		if (matching[i] == a[i].first) {
			success = false;
			break;
		}
	}

	//출력
	if (success) {
		vector<int> ans(n);
		for (int i = 0; i < n; ++i) {
			ans[a[i].second] = matching[i];
		}
		for (int i : ans)
			cout << i << " ";
	}
	else {
		cout << "-1";
	}

}