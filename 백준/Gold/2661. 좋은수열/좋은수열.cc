#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
string s;

bool DFS();
bool IsGoodSwquence();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	s.push_back(1 + '0');

	DFS();

	cout << s;

}

bool DFS() {
	if (s.size() == n)
		return true;

	for (int i = 1; i <= 3; ++i) {
		s.push_back(i + '0');
		if (IsGoodSwquence() && DFS()) {
			return true;
		}
		s.pop_back();
	}
	return false;
}

bool IsGoodSwquence() {
	for (int i = 1; i * 2 <= s.size(); ++i) {
		if(s.substr(s.size() - i, i) == s.substr(s.size() - i * 2, i) )
			return false;
	}
	return true;
}