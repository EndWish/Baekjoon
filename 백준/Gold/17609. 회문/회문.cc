#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;

bool IsPalindrome(const string& s);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	string s;
	for (int i = 0; i < n; ++i) {
		int ans = 0;

		cin >> s;

		for (int i = 0; i < s.size() / 2; ++i) {
			if (s[i] != s[s.size() - 1 - i]) {
				ans = 2;
				int popIndex = i;
				if (IsPalindrome(s.substr(0, popIndex) + s.substr(popIndex + 1, s.size() - popIndex - 1))) {
					ans = 1;
					break;
				}
				popIndex = s.size() - 1 - i;
				if (IsPalindrome(s.substr(0, popIndex) + s.substr(popIndex + 1, s.size() - popIndex - 1))) {
					ans = 1;
					break;
				}
				break;
			}
		}

		cout << ans << "\n";
	}
	
}

bool IsPalindrome(const string& s) {
	for (int i = 0; i < s.size() / 2; ++i) {
		if (s[i] != s[s.size() - 1 - i])
			return false;
	}
	return true;
}

