#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int start = -1, end = -1;
	int count = 1;
	cin >> n;
	while (0 < n) {
		if ((n & 1) && start == -1)
			start = count;
		end = count;
		++count;
		n >>= 1;
	}

	if (start == end)
		cout << (1 << (end - 1)) << " " << 0;
	else
		cout << (1 << end) << " " << end - start + 1;
}

