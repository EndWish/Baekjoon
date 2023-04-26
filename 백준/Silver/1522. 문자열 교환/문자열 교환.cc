#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

string str;
int totalA;
int bNum;
queue<char> q;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> str;
	for (char ch : str)
		if (ch == 'a')
			++totalA;

	for (int i = str.size() - totalA; i < str.size(); ++i) {
		q.push(str[i]);
		if (str[i] == 'b')
			++bNum;
	}

	int ans = numeric_limits<int>::max();
	for (int i = 0; i < str.size(); ++i) {
		q.push(str[i]);
		if (str[i] == 'b')
			++bNum;

		if (q.front() == 'b')
			--bNum;
		q.pop();

		ans = min(ans, bNum);
	}

	cout << ans;
}
