#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

string a, b;
int ans;

void setLength();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> a >> b;

	ans = a.size() + b.size();
	setLength();
	swap(a, b);
	setLength();

	cout << ans;

}

void setLength() {
	for (int aStart = 0; aStart <= a.size(); ++aStart) {
		int length = max(aStart + b.size(), a.size());

		if (ans <= length)
			continue;

		bool success = true;
		int ai = aStart;
		int bi = 0;
		while (ai < a.size() && bi < b.size()) {
			if (a[ai] == b[bi] && a[ai] == '2') {
				success = false;
				break;
			}
			++ai;
			++bi;
		}

		if (success) {
			ans = length;
		}
	}

}
