#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n;
stack<pii> heights;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int height;
		cin >> height;

		while (!heights.empty() && heights.top().first < height)
			heights.pop();

		if (heights.empty())
			cout << 0 << " ";
		else
			cout << heights.top().second << " ";
		heights.emplace(height, i);

	}
}

