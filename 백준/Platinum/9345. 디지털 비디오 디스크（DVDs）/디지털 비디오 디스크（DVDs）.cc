#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

#define pii pair<int,int>
#define MAXN 10'001

int t, n, k;
vector<int> nums;
vector<pii> seg;

void MakeSegTree(int index, int start, int end);
void Change(int index, int start, int end, int pos, int num);
pii GetLR(int index, int start, int end, int left, int right);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> n >> k;
		nums.assign(n + 1, {});
		iota(nums.begin(), nums.end(), 0);
		seg.assign(n * 4 + 1, {});
		MakeSegTree(1, 1, n);

		//문제해결
		int q, a, b;
		for (int i = 0; i < k; ++i) {
			cin >> q >> a >> b;
			++a; ++b;
			if (q == 0) {
				Change(1, 1, n, a, nums[b]);
				Change(1, 1, n, b, nums[a]);
				swap(nums[a], nums[b]);
			}
			else {
				if (make_pair(a, b) == GetLR(1, 1, n, a, b))
					cout << "YES\n";
				else
					cout << "NO\n";
			}

		}

	}
}

void MakeSegTree(int index, int start, int end) {
	if (start == end) {
		seg[index].first = nums[start];
		seg[index].second = nums[start];
		return;
	}
	
	int mid = (start + end) / 2;
	MakeSegTree(index * 2, start, mid);
	MakeSegTree(index * 2 + 1, mid + 1, end);
	seg[index].first = min(seg[index * 2].first, seg[index * 2 + 1].first);
	seg[index].second = max(seg[index * 2].second, seg[index * 2 + 1].second);
}

void Change(int index, int start, int end, int pos, int num) {
	if (start == end) {
		seg[index].first = num;
		seg[index].second = num;
		return;
	}

	int mid = (start + end) / 2;
	if (start <= pos && pos <= mid)
		Change(index * 2, start, mid, pos, num);
	else
		Change(index * 2 + 1, mid + 1, end, pos, num);

	seg[index].first = min(seg[index * 2].first, seg[index * 2 + 1].first);
	seg[index].second = max(seg[index * 2].second, seg[index * 2 + 1].second);
}

pii GetLR(int index, int start, int end, int left, int right) {
	if (left <= start && end <= right)
		return seg[index];
	if (end < left || right < start)
		return { numeric_limits<int>::max(),numeric_limits<int>::min() };

	int mid = (start + end) / 2;
	pii leftResult = GetLR(index * 2, start, mid, left, right);
	pii rightResult = GetLR(index * 2 + 1, mid + 1, end, left, right);

	return { min(leftResult.first, rightResult.first), max(leftResult.second, rightResult.second) };

}
