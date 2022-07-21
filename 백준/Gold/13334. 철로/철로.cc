#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#define pii pair<int,int>

using namespace std;


int n, d;
vector<pii> otthSortedFirst;	// office to the house
vector<pii> otthSortedSecond;	// office to the house

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);	

	//최기화,입력값 받기
	cin >> n;
	otthSortedFirst.assign(n, make_pair(0, 0));

	for (auto& e : otthSortedFirst) {
		cin >> e.first >> e.second;
		if (e.first > e.second)
			swap(e.first, e.second);
	}
	cin >> d;
	auto p = ranges::remove_if(otthSortedFirst, [](pii e) { return d < e.second - e.first; });
	otthSortedFirst.erase(p.begin(), p.end());

	otthSortedSecond.reserve(n);
	ranges::copy(otthSortedFirst, back_inserter(otthSortedSecond));
	ranges::sort(otthSortedFirst, {}, &pii::first);
	ranges::sort(otthSortedSecond, {}, &pii::second);

	//문제해결
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int s = otthSortedFirst[i].first;	// 선분 L의 시작하는 점
		int e = s + d;	// 선분 L의 끝나는 점

		auto p2 = ranges::upper_bound(otthSortedSecond, e, {}, &pii::second);
		int includeNum = ranges::distance(otthSortedSecond.begin(), p2) - i;
		ans = max(ans, includeNum);
	}

	//출력
	cout << ans;
	
}