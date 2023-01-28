#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;
vector<int> nums;
vector<vector<int>> seg;

void MakeSeg(int index, int start, int end);
int K(int index, int start, int end, int left, int right, int x);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	nums.assign(n + 1, {});
	seg.assign(n * 4 + 1, {});
	for (int& num : nums | views::drop(1))
		cin >> num;

	MakeSeg(1, 1, n);

	//문제해결
	for (int i = 0; i < m; ++i) {
		int left, right, k;
		cin >> left >> right >> k;

		int s = -1e9;
		int e = 1e9;
		while (s < e) {
			int mid;
			if(s + e >= 0)
				mid = (s + e) / 2;
			else
				mid = (s + e - 1) / 2;
			
			if (k <= K(1, 1, n, left, right, mid)) 
				e = mid ;
			else
				s = mid + 1;
		}

		cout << s << "\n";
	}

}

void MakeSeg(int index, int start, int end) {
	if (start == end) {
		seg[index].push_back(nums[start]);
		return;
	}

	int mid = (start + end) / 2;
	MakeSeg(index * 2, start, mid);
	MakeSeg(index * 2 + 1, mid + 1, end);

	seg[index].reserve(seg[index * 2].size() + seg[index * 2 + 1].size());
	ranges::merge(seg[index * 2], seg[index * 2 + 1], back_inserter(seg[index]));
}

int K(int index, int start, int end, int left, int right, int x) {
	if (end < left || right < start)
		return 0;

	if (left <= start && end <= right) {
		return ranges::distance(seg[index].begin(), ranges::upper_bound(seg[index], x));
	}

	int mid = (start + end) / 2;
	return K(index * 2, start, mid, left, right, x) + K(index * 2 + 1, mid + 1, end, left, right, x);
}
