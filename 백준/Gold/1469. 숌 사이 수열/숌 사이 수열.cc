#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
vector<int> x;
vector<bool> visit;
vector<int> result;

bool DFS(int index);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	x.assign(n, {});
	visit.assign(n, false);
	result.assign(n * 2, -1);
	for (int& num : x)
		cin >> num;

	ranges::sort(x);

	if (DFS(0)) {
		for (int num : result)
			cout << num << " ";
	}
	else {
		cout << -1;
	}
}

bool DFS(int index) {
	if (index == result.size())
		return true;

	if (result[index] != -1) {
		if (DFS(index + 1)) {
			return true;
		}
	}
	else {
		for (int i = 0; i < x.size(); ++i) {
			if (!visit[i]) {
				int pairIndex = index + x[i] + 1;
				if (pairIndex < result.size() && result[pairIndex] == -1) {
					result[index] = x[i];
					result[pairIndex] = x[i];
					visit[i] = true;
					if (DFS(index + 1)) {
						return true;
					}
					else {
						result[index] = -1;
						result[pairIndex] = -1;
						visit[i] = false;
					}
				}
			}
		}
	}

	return false;
}
