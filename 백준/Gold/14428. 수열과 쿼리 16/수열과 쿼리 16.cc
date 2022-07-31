#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

#define pii pair<int,int>

using namespace std;

int n, m;
vector<int> nums;
vector<pii> segTree;

void MakeSegTree(int index, int left, int right);
void ChangeNum(int index, int left, int right, int pos, int num);
pii GetIndex(int index, int left, int right, int start, int end);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	nums.assign(n + 1, 0);
	segTree.assign(n * 4, {0,0});

	for (int& val : nums | views::drop(1))
		cin >> val;

	//문제해결
	MakeSegTree(1, 1, n);

	cin >> m;
	int cmd, a, b;
	for (int i = 0; i < m; ++i) {
		cin >> cmd >> a >> b;
		if (cmd == 1) {
			ChangeNum(1, 1, n, a, b);	// a번째 수를 b로 바꾼다.
		}
		else {
			cout << GetIndex(1, 1, n, a, b).second << "\n";	// a~b중 가장 작은 값의 인덱스 출력
		}
	}

	//출력
	
}

void MakeSegTree(int index, int left, int right) {
	if (left == right) {
		segTree[index] = { nums[left], left };	// {값, 인덱스}
		return;
	}

	int mid = (left + right) / 2;
	MakeSegTree(index * 2, left, mid);
	MakeSegTree(index * 2 + 1, mid + 1, right);
	segTree[index] = segTree[index * 2].first <= segTree[index * 2 + 1].first ? segTree[index * 2] : segTree[index * 2 + 1];

}

void ChangeNum(int index, int left, int right, int pos, int num) {
	if (left == right) {	// left == right == pos
		segTree[index].first = num;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= pos && pos <= mid) {
		ChangeNum(index * 2, left, mid, pos, num);
	}
	else {
		ChangeNum(index * 2 + 1, mid + 1, right, pos, num);
	}
	segTree[index] = segTree[index * 2].first <= segTree[index * 2 + 1].first ? segTree[index * 2] : segTree[index * 2 + 1];

}

pii GetIndex(int index, int left, int right, int start, int end) {
	if (start <= left && right <= end) {
		return segTree[index];
	}
	if (right < start || end < left) {
		return { numeric_limits<int>::max(), 0 };
	}

	int mid = (left + right) / 2;
	pii leftRes = GetIndex(index * 2, left, mid, start, end);
	pii rightRes = GetIndex(index * 2 + 1, mid + 1, right, start, end);
	return leftRes.first <= rightRes.first ? leftRes : rightRes;
}