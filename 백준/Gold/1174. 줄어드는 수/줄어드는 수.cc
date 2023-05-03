#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
string s;

bool next(string& str);
void upgrade(string& str, int index);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	s.push_back(0);
	for (int i = 0; i < n - 1; ++i) {
		bool result = next(s);

		if (!result) {
			cout << -1;
			return 0;
		}
	}

	for (char ch : s)
		cout << (int)ch;
}

bool next(string& str) {

	for (int i = str.size() - 1; 0 <= i; --i) {
		if (i == 0) {
			if (str[i] < 9)
				upgrade(str, i);
			else {
				str.push_back(0);
				if (10 < str.size())
					return false;
				int count = 0;
				for (int i = str.size() - 1; 0 <= i; --i) {
					str[i] = count++;
				}
			}
		}
		else {
			if (str[i] < str[i - 1] - 1) {
				upgrade(str, i);
				break;
			}
		}
	}

	return true;
}

void upgrade(string& str, int index) {
	++str[index];

	int count = 0;
	for (int i = str.size() - 1; index < i; --i) {
		str[i] = count++;
	}
}
