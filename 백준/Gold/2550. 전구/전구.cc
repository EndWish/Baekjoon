#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 10'001
#define pii pair<int,int>

int n;
array<int, MAXN> buttonNumToIndex;
vector<pii> buttons;	// 연결된 전구의 index, 스위치 번호

vector<pii> dp;	// 연결된 전구의 index, 스위치 번호
array<int, MAXN> path;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		pii button;
		cin >> button.second;
		buttonNumToIndex[button.second] = i;
		buttons.push_back(button);
	}
	for (int i = 0; i < n; ++i) {
		int bulb;
		cin >> bulb;
		buttons[buttonNumToIndex[bulb]].first = i;
	}

	//문제해결
	int ansNum = buttons[0].second;
	path[buttons[0].second] = -1;
	dp.push_back(buttons[0]);

	for (int i = 1; i < n; ++i) {
		auto [bulbIndex, switchNum] = buttons[i];
		auto p = ranges::lower_bound(dp, bulbIndex, {}, &pii::first);
		if (p == dp.end()) {	// 새로 켤 수 있는 전구일 경우
			path[switchNum] = dp.back().second;
			dp.push_back(buttons[i]);
			ansNum = switchNum;
		}
		else if(p != dp.begin()) {
			path[switchNum] = (p - 1)->second;
			*p = buttons[i];
		}
		else {
			path[switchNum] = -1;
			*p = buttons[i];
		}
	}

	//출력
	vector<int> ans;
	while (true) {
		ans.push_back(ansNum);
		ansNum = path[ansNum];
		if (ansNum == -1)
			break;
	}

	ranges::sort(ans);
	cout << ans.size() << "\n";
	for (int value : ans)
		cout << value << " ";

}