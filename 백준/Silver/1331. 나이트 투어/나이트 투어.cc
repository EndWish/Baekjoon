#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define pii pair<int,int>

int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

array<array<bool, 6>, 6> visit;
vector<pii> poses;

bool CanMove(int index);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	for(int i = 0; i < 36; ++i){
		char ch1, ch2;
		cin >> ch1 >> ch2;

		pii pos(ch1 - 'A', ch2 - '1');
		poses.push_back(pos);
	}

	//문제해결
	for (int i = 0; i < 36; ++i) {
		int x = poses[i].first;
		int y = poses[i].second;
		if (visit[x][y] || !CanMove(i)) {
			cout << "Invalid";
			return 0;
		}
		visit[x][y] = true;
	}

	//출력
	cout << "Valid";

}

bool CanMove(int index) {
	int preIndex = (index - 1 + 36) % 36;

	int x = poses[preIndex].first;
	int y = poses[preIndex].second;

	for (int i = 0; i < 8; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx == poses[index].first && ny == poses[index].second)
			return true;
	}
	return false;
}