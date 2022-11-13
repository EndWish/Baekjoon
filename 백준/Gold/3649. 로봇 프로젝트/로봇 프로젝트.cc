#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int x, n;
vector<int> regos;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


	while (cin >> x) {
		//초기화,입력값 받기
		x = x * 10'000'000;
		cin >> n;
		regos.assign(n, {});
		for (int& rego : regos)
			cin >> rego;

		//문제해결
		bool success = false;
		ranges::sort(regos);
		for (auto it = regos.begin(); it != regos.end(); ++it) {
			int target = x - *it;
			if (ranges::binary_search(it + 1, regos.end(), target)) {
				cout << "yes " << *it << " " << target << "\n";
				success = true;
				break;
			}
		}

		if (!success)
			cout << "danger\n";

		//출력
	}



}