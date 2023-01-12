#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n, m;
vector<ll> nums;
vector<ll> seg, lazy;

void InitSeg(int index, int start, int end);
void ChangeSeg(int index, int start, int end, int left, int right, ll add);
ll GetNum(int index, int start, int end, int pos);
void Update(int index, int start, int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n + 1, {});
	for (ll& num : nums | views::drop(1))
		cin >> num;

	seg.assign(n * 4 + 1, {});
	lazy.assign(n * 4 + 1, {});
	InitSeg(1, 1, n);



	//문제해결
	cin >> m;
	int cmd, a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> cmd;
		if (cmd == 1) {
			cin >> a >> b >> c;
			ChangeSeg(1, 1, n, a, b, c);
		}
		else if(cmd == 2) {
			cin >> a;
			cout << GetNum(1, 1, n, a) << "\n";
		}

	}

	//출력

}

void InitSeg(int index, int start, int end) {
	if (start == end) {
		seg[index] = nums[start];
		return;
	}

	int mid = (start + end) / 2;
	InitSeg(index * 2, start, mid);
	InitSeg(index * 2 + 1, mid + 1, end);
	seg[index] = seg[index * 2] + seg[index * 2 + 1];

}

void ChangeSeg(int index, int start, int end, int left, int right, ll add) {
	if (right < start || end < left)
		return;

	if (left <= start && end <= right) {
		lazy[index] += add;
		return;
	}

	int mid = (start + end) / 2;
	ChangeSeg(index * 2, start, mid, left, right, add);
	ChangeSeg(index * 2 + 1, mid + 1, end, left, right, add);
}

ll GetNum(int index, int start, int end, int pos) {
	if (lazy[index] != 0)
		Update(index, start, end);

	if (start == end)
		return seg[index];

	int mid = (start + end) / 2;
	if (start <= pos && pos <= mid)
		return GetNum(index * 2, start, mid, pos);
	else
		return GetNum(index * 2 + 1, mid + 1, end, pos);

}

void Update(int index, int start, int end) {
	seg[index] += lazy[index] * (end - start + 1);
	if (start != end) {
		lazy[index * 2] += lazy[index];
		lazy[index * 2 + 1] += lazy[index];
	}
	lazy[index] = 0;
}
