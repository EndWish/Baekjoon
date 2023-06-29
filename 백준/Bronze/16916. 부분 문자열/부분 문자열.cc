#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <functional>

using namespace std;

vector<int> Fail(const string& str);
bool KMP(const string& text, const string& pattern);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	string text, pattern;
    cin >> text >> pattern;
	
	cout << KMP(text, pattern) ? '1' : '0';

}

vector<int> Fail(const string& str) {
	vector<int> failure;
	failure.assign(str.size(), -1);

	int j = 0;
	for (int i = 1; i < str.size(); ++i) {
		while (j > 0 && str[j] != str[i]) {
			j = failure[j - 1] + 1;
		}

		if (str[j] == str[i]) {
			failure[i] = j;
			++j;
		}
		else {
			failure[i] = -1;
		}
	}

	return failure;
}

bool KMP(const string& text, const string& pattern) {
	vector<int> failure = Fail(pattern);

	int j = 0;
	for (int i = 0; i < text.size(); ++i) {
		
		while (j > 0 && text[i] != pattern[j]) {
			j = failure[j - 1] + 1;
		}
		
		if (text[i] == pattern[j]) {
			if (++j == pattern.size()) {
				return true;
			}
		}
	}

	return false;
}
