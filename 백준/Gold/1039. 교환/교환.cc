#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

string input;
int k;
unordered_set<string> curSet, nextSet;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> input >> k;
	ranges::transform(input, input.begin(), [](char ch) {return ch - '0'; });

	//문제해결
	if (input.size() <= 1) {
		cout << -1;
		return 0;
	}

	curSet.insert(input);
	while (k-- > 0) {
		for (const string& num : curSet) {
			for (int i = 0; i < num.size() - 1; ++i) {
				for (int j = i + 1; j < num.size(); ++j) {
					string nextNum = num;
					swap(nextNum[i], nextNum[j]);
					if (nextNum[0] != 0)
						nextSet.insert(nextNum);
				}
			}
		}

		if (nextSet.size() == 0) {
			cout << -1;
			return 0;
		}

		curSet = move(nextSet);
		nextSet.clear();
	}

	auto it = ranges::max_element(curSet);
	for (char ch : *it)
		cout << (int)ch;

}
