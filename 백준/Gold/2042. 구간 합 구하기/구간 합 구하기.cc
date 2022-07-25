#include <iostream>
#include <vector>

#define ll long long

using namespace std;

int n, m, k;
vector<ll> nums;
vector<ll> sums;
vector<ll> segTree;

void MakeSegTree(int index, int left, int right);
void ChangeNum(int index, int left, int right, int pos, ll num);
ll GetSum(int index, int left, int right, int start, int end);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m >> k;
	nums.assign(n, 0);
	sums.assign(n, 0);
	segTree.assign(n * 4, 0);

	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
		if (i == 0)
			sums[i] = nums[i];
		else
			sums[i] = sums[i - 1] + nums[i];
	}

	//문제해결
	MakeSegTree(1, 0, n - 1);

	ll cmd, a, b;
	for (int i = 0; i < m + k; ++i) {
		cin >> cmd >> a >> b;
		if (cmd == 1) {	// n번째 수를 바꾸기
			ChangeNum(1, 0, n - 1, a - 1, b);
		}
		else {	// [a,b]까지의 합 출력
			cout << GetSum(1, 0, n - 1, a - 1, b - 1) << "\n";
		}

	}

	//출력
	
}

void MakeSegTree(int index, int left, int right) 
{
	if (left == right) {
		segTree[index] = sums[right] - sums[left] + nums[left];
		return;
	}

	int mid = (left + right) / 2;
	MakeSegTree(index * 2, left, mid);
	MakeSegTree(index * 2 + 1, mid + 1, right);
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

void ChangeNum(int index, int left, int right, int pos, ll num) {

	if (left == right) {
		segTree[index] = num;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= pos && pos <= mid) {
		ChangeNum(index * 2, left, mid, pos, num);
	}
	else {
		ChangeNum(index * 2 + 1, mid + 1, right, pos, num);
	}

	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

ll GetSum(int index, int left, int right, int start, int end) {

	if (start <= left && right <= end) {
		return segTree[index];
	}
	if (right < start) {
		return 0;
	}
	if (end < left) {
		return 0;
	}

	int mid = (left + right) / 2;
	ll res = GetSum(index * 2, left, mid, start, end) + GetSum(index * 2 + 1, mid + 1, right, start, end);

	return res;
}
