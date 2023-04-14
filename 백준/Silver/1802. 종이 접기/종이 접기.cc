#include <iostream>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

bool CanFold(const string& s);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;

	string s;
	while (t-- > 0) {
		cin >> s;
		if (CanFold(s))
			cout << "YES\n";
		else
			cout << "NO\n";
	}

}

bool CanFold(const string& s) {
	for (int i = 0; i < s.size() / 2; ++i) {
		if (s[i] == s[s.size() - 1 - i])
			return false;
	}

	if (1 < s.size()) {
		int center = s.size() / 2;
		if (!CanFold(s.substr(0, center)))
			return false;
		if (!CanFold(s.substr(center + 1, center)))
			return false;
	}

	return true;
}