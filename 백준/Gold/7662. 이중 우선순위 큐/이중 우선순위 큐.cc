#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int k, n;
char cmd;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		multiset<int> mset;
		cin >> k;

		//문제해결
		for (int i = 0; i < k; ++i) {
			cin >> cmd >> n;
			if (cmd == 'I') {
				mset.insert(n);
			}
			else if (cmd == 'D' && !mset.empty()) {
				if (n == 1) {
					auto it = mset.end();
					ranges::advance(it, -1);
					mset.erase(it);
				}
				else {
					mset.erase(mset.begin());
				}
			}
		}

		if (mset.empty()) {
			cout << "EMPTY\n";
		}
		else {
			cout << *mset.rbegin() << " " << *mset.begin() << "\n";
		}
	}

}

