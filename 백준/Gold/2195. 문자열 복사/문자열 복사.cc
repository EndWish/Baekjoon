#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;



int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	string s, p;
	cin >> s >> p;

	int result = 0;
	for (int i = 0; i < p.size();) {
		int maxLen = 0;
		for (int j = 0; j < s.size(); ++j) {
			int len = 0;
			while (s[j + len] == p[i + len])
				++len;
			maxLen = max(maxLen, len);
		}
		i += maxLen;
		++result;
	}
	cout << result;
}

