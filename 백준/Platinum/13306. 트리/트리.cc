#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <tuple>

using namespace std;

int n, m;
vector<int> parents;
vector<int> belongs;
vector<array<int, 3>> cmds;

int Find(int x);
void Unite(int a, int b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	parents.assign(n + 1, {});
	belongs.assign(n + 1, {});
	iota(belongs.begin(), belongs.end(), 0);
	cmds.assign(n - 1 + m, {});

	for (int i = 2; i <= n; ++i) {
		cin >> parents[i];
	}
	for (array<int, 3>& cmd : cmds) {
		cin >> cmd[0];
		if (cmd[0] == 0) {
			cin >> cmd[1];
		}
		else {
			cin >> cmd[1] >> cmd[2];
		}
	}
	
	vector<bool> anses;
	for (array<int, 3>&cmd : cmds | views::reverse) {
		if (cmd[0] == 0) {
			Unite(cmd[1], parents[cmd[1]]);
		}
		else {
			if (Find(cmd[1]) == Find(cmd[2]))
				anses.push_back(true);
			else
				anses.push_back(false);
		}
	}

	reverse(anses.begin(), anses.end());
	for (bool ans : anses) {
		if (ans)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

}

int Find(int x) {
	if (x == belongs[x])
		return x;
	return belongs[x] = Find(belongs[x]);
}

void Unite(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a > b)
		swap(a, b);

	belongs[b] = a;
}
