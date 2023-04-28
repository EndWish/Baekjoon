#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <iomanip>
#include <cmath>

using namespace std;

#define pii pair<int,int>

int n;
vector<pii> poses;
vector<int> parents;

int Find(int x);
void Unite(int x, int y);
int GetDistance(pii& a, pii& b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t-- > 0) {
		poses.clear();
		parents.clear();

		cin >> n;

		pii input;
		for (int i = 0; i < n + 2; ++i) {
			cin >> input.first >> input.second;
			poses.push_back(input);
			parents.push_back(parents.size());
		}

		for (int i = 0; i < poses.size(); ++i) {
			for (int j = i + 1; j < poses.size(); ++j) {
				if (Find(i) != Find(j) && GetDistance(poses[i], poses[j]) <= 1000) {
					Unite(i, j);
				}
			}
		}

		cout << ((Find(0) != Find(poses.size() - 1)) ? "sad\n" : "happy\n");
	}


	
}

int Find(int x) {
	if (x == parents[x])
		return x;
	return parents[x] = Find(parents[x]);
}

void Unite(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x > y)
		swap(x, y);
	parents[y] = x;
}

int GetDistance(pii& a, pii& b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}