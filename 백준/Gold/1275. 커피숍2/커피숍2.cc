#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define ll long long
#define MAXN 100'001

int n, q;
vector<ll> nums;
vector<ll> segTree;

void MakeSegTree(int index, int left, int right);
ll GetSum(int index, int left, int right, int start, int end);
void ChangeNum(int index, int left, int right, int pos, ll num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	// 커피숍2 - 1275
	cin >> n >> q;
	nums.assign(n + 1, {});
	segTree.assign(4 * n + 1, {});

	for (ll& num : nums | views::drop(1))
		cin >> num;

	//문제해결
	MakeSegTree(1, 1, n);

	for (int i = 0; i < q; ++i) {
		ll x, y, a, b;
		cin >> x >> y >> a >> b;
		
		if (x > y)
			swap(x, y);
		cout << GetSum(1, 1, n, x, y) << "\n";
		if(1 <= a && a <= n)
			ChangeNum(1, 1, n, a, b);
	}

	//출력

}

void MakeSegTree(int index, int left, int right) {
	if (left == right) {
		segTree[index] = nums[left];
		return;
	}

	int mid = (left + right) / 2;
	MakeSegTree(index * 2, left, mid);
	MakeSegTree(index * 2 + 1, mid + 1, right);
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

ll GetSum(int index, int left, int right, int start, int end) {
	// 범위밖인 경우
	if (right < start || end < left)
		return 0;

	// 범위안인 경우
	if (start <= left && right <= end)
		return segTree[index];

	// 걸치는 경우
	int mid = (left + right) / 2;
	ll lvalue = GetSum(index * 2, left, mid, start, end);
	ll rvalue = GetSum(index * 2 + 1, mid + 1, right, start, end);
	return lvalue + rvalue;
}

void ChangeNum(int index, int left, int right, int pos, ll num) {
	if (right == left && left == pos) {
		nums[pos] = num;
		segTree[index] = num;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= pos && pos <= mid)
		ChangeNum(index * 2, left, mid, pos, num);
	else
		ChangeNum(index * 2 + 1, mid + 1, right, pos, num);
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

