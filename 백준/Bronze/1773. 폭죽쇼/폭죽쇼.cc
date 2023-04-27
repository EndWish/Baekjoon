#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <iomanip>

using namespace std;

int n, c;
array<bool, 2'000'001> fire;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> c;

	int input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		if (!fire[input]) {
			for (int j = input; j <= c; j += input) {
				fire[j] = true;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= c; ++i) {
		if (fire[i])
			++ans;
	}
	cout << ans;
}
