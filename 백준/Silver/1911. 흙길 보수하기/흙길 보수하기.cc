#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, l;
vector<pii> poses;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> l;
	poses.assign(n, {});
	for (auto& [s, e] : poses)
		cin >> s >> e;
	ranges::sort(poses);

	int ans = 0;
	int boardPos = 0;
	for (auto[s, e] : poses) {
		if (e <= boardPos)
			continue;

		if (boardPos < s) {	// 새로운 위치에서 다시 널판지를 깔아야 할 경우
			boardPos = s;
		}

		int addBoard = (e - boardPos + l - 1) / l;
		boardPos += addBoard * l;
		ans += addBoard;
	}
	
	cout << ans;
}


