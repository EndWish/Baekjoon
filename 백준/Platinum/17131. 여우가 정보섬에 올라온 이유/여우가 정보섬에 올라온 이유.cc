#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
#define ll long long
#define MAXWID 400'001
#define offset 200'001
#define MOD 1'000'000'007

int n;
vector<pii> points;

vector<int> seg;

void PushStar(int index, int start, int end, int x);
ll GetStar(int index, int start, int end, int left, int right);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	points.assign(n, {});
	seg.assign(MAXWID * 4 + 1, {});
	for (auto& [x, y] : points)
		cin >> x >> y;

	auto comp = [](const pii& a, const pii& b) {
		return a.second > b.second;
	};
	ranges::sort(points, comp);

	//문제해결
	int currentHeight = numeric_limits<int>::max();
	queue<int> q;

	ll ans = 0;
	for (auto [x, y] : points) {
		if (currentHeight > y) {
			while (!q.empty()) {
				PushStar(1, 1, MAXWID, q.front() + offset);
				q.pop();
			}
			currentHeight = y;
		}
		q.push(x);

		ll leftStars = GetStar(1, 1, MAXWID, 0, x - 1 + offset);
		ll rightStars = GetStar(1, 1, MAXWID, x + 1 + offset, MAXWID);
		ans += (leftStars * rightStars) % MOD;
		ans %= MOD;
	}

	cout << ans;
	
}

void PushStar(int index, int start, int end, int x) {
	if (start == end) {
		++seg[index];
		return;
	}

	int mid = (start + end) / 2;
	if(start <= x && x <= mid)
		PushStar(index * 2, start, mid, x);
	else
		PushStar(index * 2 + 1, mid + 1, end, x);
	seg[index] = seg[index * 2] + seg[index * 2 + 1];
}

ll GetStar(int index, int start, int end, int left, int right) {
	if (left <= start && end <= right)
		return seg[index];
	if (end < left || right < start)
		return 0;

	int mid = (start + end) / 2;
	return GetStar(index * 2, start, mid, left, right) + GetStar(index * 2 + 1, mid + 1, end, left, right);
}
