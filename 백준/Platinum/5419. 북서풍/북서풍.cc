#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <ranges>

using namespace std;

#define pii pair<int,int>
#define MAXH 75'000
#define ll long long

int n;
vector<pii> points;
map<int, int> heights;
array<int, MAXH * 4 + 4> seg;

void PushHeight(int index, int start, int end, int height);
int GetNumOfMoreThanHeight(int index, int start, int end, int height);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> n;
		points.assign(n, {});
		heights.clear();
		seg.fill(0);

		for (pii& point : points) {
			cin >> point.first >> point.second;
			heights[point.second] = 0;
		}
		
		for (int i = 1; auto & [y, h] : heights) {
			h = i++;
		}


		//문제해결
		// x값 기준으로 오름차순으로 정렬, x가 같으면 y가 큰것 부터
		auto comp = [](const pii& a, const pii& b) {
			if (a.first == b.first)
				return a.second > b.second;
			return a.first < b.first;
		};
		ranges::sort(points, comp);

		ll ans = 0;
		for (auto point : points) {
			ans += (ll)GetNumOfMoreThanHeight(1, 1, MAXH, heights[point.second]);
			PushHeight(1, 1, MAXH, heights[point.second]);
		}
		cout << ans << "\n";
	}
}

void PushHeight(int index, int start, int end, int height) {
	if (start == end) {
		++seg[index];
		return;
	}

	int mid = (start + end) / 2;
	if(start <= height && height <= mid)
		PushHeight(index * 2, start, mid, height);
	else
		PushHeight(index * 2 + 1, mid + 1, end, height);

	seg[index] = seg[index * 2] + seg[index * 2 + 1];
}

int GetNumOfMoreThanHeight(int index, int start, int end, int height) {
	if (height <= start) {
		return seg[index];
	}
	if (end < height) {
		return 0;
	}

	int result = 0;
	int mid = (start + end) / 2;
	result += GetNumOfMoreThanHeight(index * 2, start, mid, height);
	result += GetNumOfMoreThanHeight(index * 2 + 1, mid + 1, end, height);
	return result;
}
