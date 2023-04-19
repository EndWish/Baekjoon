#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n;
vector<int> downMans, upMans, downWomans, upWomans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	int input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		if (0 < input)
			upMans.push_back(input);
		else
			downMans.push_back(-input);
	}
	for (int i = 0; i < n; ++i) {
		cin >> input;
		if (0 < input)
			upWomans.push_back(input);
		else
			downWomans.push_back(-input);
	}

	ranges::sort(upMans);
	ranges::sort(downMans);
	ranges::sort(upWomans);
	ranges::sort(downWomans);

	int ans = 0;

	int index = 0;
	for (int upWoman : upWomans) {
		while (index < downMans.size() && downMans[index] <= upWoman)
			++index;
		if (downMans.size() <= index)
			break;
		++ans;
		++index;
	}

	index = 0;
	for (int upMan : upMans) {
		while (index < downWomans.size() && downWomans[index] <= upMan)
			++index;
		if (downWomans.size() <= index)
			break;
		++ans;
		++index;
	}
	cout << ans;
}
