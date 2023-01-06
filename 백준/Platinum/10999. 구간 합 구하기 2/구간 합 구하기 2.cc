#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
//#include <format>

using namespace std;

#define ll long long

int n, m, k;
vector<ll> nums, seg, lazy;

void InitSegTree(int index, int start, int end);
void Changes(int index, int start, int end, int left, int right, ll add);
ll Sum(int index, int start, int end, int left, int right);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	nums.assign(n + 1, {});
	seg.assign(n * 4 + 1, {});
	lazy.assign(n * 4 + 1, {});
	for (ll& num : nums | views::drop(1))
		cin >> num;

	InitSegTree(1, 1, n);

	//문제해결
	ll a, b, c, d;
	for (int i = 0; i < m + k; ++i) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			Changes(1, 1, n, b, c, d);
		}
		else if(a == 2) {
			cin >> b >> c;
			cout << Sum(1, 1, n, b, c) << "\n";
		}
	}

	//출력

}

void InitSegTree(int index, int start, int end) {
	if (start == end) {
		seg[index] = nums[start];
		return;
	}

	int mid = (start + end) / 2;
	InitSegTree(index * 2, start, mid);
	InitSegTree(index * 2 + 1, mid + 1, end);
	seg[index] = seg[index * 2] + seg[index * 2 + 1];
}

void Changes(int index, int start, int end, int left, int right, ll add) {
	if (right < start || end < left)
		return;
	if (left <= start && end <= right) {
		lazy[index] += add;
		//cout << format("lazy삽입 : {}~{} : {}\n", start, end, add);
		return;
	}
	
	seg[index] += add * (min(end, right) - max(start, left) + 1);
	int mid = (start + end) / 2;
	Changes(index * 2, start, mid, left, right, add);
	Changes(index * 2 + 1, mid + 1, end, left, right, add);
}

ll Sum(int index, int start, int end, int left, int right) {
	// 느리게 갱신
	if (lazy[index] != 0) {
		seg[index] += lazy[index] * (end - start + 1);
		//cout << format("lazy적용 : {}~{} : {}\n", start, end, lazy[index]);
		if (start < end) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}

	if (right < start || end < left)
		return 0;
	if (left <= start && end <= right) {
		return seg[index];
	}

	int mid = (start + end) / 2;
	return Sum(index * 2, start, mid, left, right) + Sum(index * 2 + 1, mid + 1, end, left, right);
}
