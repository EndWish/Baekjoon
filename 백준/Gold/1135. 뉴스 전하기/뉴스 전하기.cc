#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

int n;
array<vector<int>, 50> children;

int DFS(int node);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int parent;
		cin >> parent;
		if(parent != -1)
			children[parent].push_back(i);
	}

	cout << DFS(0);

}

int DFS(int node) {
	int result = 0;

	vector<int> times;
	times.reserve(children[node].size());
	for (int child : children[node]) {
		times.push_back(DFS(child));
	}

	ranges::sort(times, greater<int>{});
	for (int i = 0; i < times.size(); ++i) {
		result = max(times[i] + (i + 1), result);
	}

	return result;
}
