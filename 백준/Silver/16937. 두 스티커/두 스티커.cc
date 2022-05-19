#include <iostream>
#include <algorithm>
#include <vector>

#define pii pair<int,int>

using namespace std;

int h, w, n;
vector<pii> sticker;

int Post(pii a, pii b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> h >> w >> n;
	sticker.assign(n, { 0,0 });
	for (int i = 0; i < n; ++i)
		cin >> sticker[i].first >> sticker[i].second;

	//문제해결
	int result = 0;
	for (auto it1 = sticker.begin(); it1 != sticker.end(); ++it1) {
		for (auto it2 = it1 + 1; it2 != sticker.end(); ++it2) {
			result = max(result, Post(*it1, *it2));
		}
	}
	
	//출력
	cout << result;
}

int Post(pii a, pii b) {
	auto[x1, y1] = a;
	auto[x2, y2] = b;

	for (int i = 0; i < 2; ++i) {	// a를 회전
		for (int j = 0; j < 2; ++j) {	// b를 회전

			if(max(x1, x2) <= w && y1 + y2 <= h)	// 위아래로 붙이기
				return x1 * y1 + x2 * y2;
			if (x1 + x2 <= w && max(y1, y2) <= h)	//양옆으로 붙이기
				return x1 * y1 + x2 * y2;

			swap(x2, y2);
		}
		swap(x1, y1);
	}

	return 0;
}

