#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

#define pii pair<int,int>

using namespace std;

int n, m;
vector<int> nums;
vector<int> segTreeMax;
vector<int> segTreeMin;

void MakeSegTree(int index, int left, int right);
pii MaxMinNum(int index, int left, int right, int start, int end);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	nums.assign(n + 1, 0);
	segTreeMax.assign(n * 4, 0);
	segTreeMin.assign(n * 4, 0);

	for (int& val : nums | views::drop(1)) {
		cin >> val;
	}

	//문제해결
	MakeSegTree(1, 1, n);

	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		auto [maxNum, minNum] = MaxMinNum(1, 1, n, a, b);
		cout << minNum << " " << maxNum << "\n";
	}

	//출력
	
}

void MakeSegTree(int index, int left, int right) {

	if (left == right) {
		segTreeMax[index] = nums[left];
		segTreeMin[index] = nums[left];
		return;
	}

	int mid = (left + right) / 2;
	MakeSegTree(index * 2, left, mid);
	MakeSegTree(index * 2 + 1, mid + 1, right);
	segTreeMax[index] = max(segTreeMax[index * 2], segTreeMax[index * 2 + 1]);
	segTreeMin[index] = min(segTreeMin[index * 2], segTreeMin[index * 2 + 1]);

}

pii MaxMinNum(int index, int left, int right, int start, int end) {
	if (start <= left && right <= end) {	// 범위안에 포함되는 경우
		return make_pair(segTreeMax[index], segTreeMin[index]);
	}
	if (right < start || end < left) {	// 범위 밖일경우
		return {numeric_limits<int>::min(), numeric_limits<int>::max() };
	}

	int mid = (left + right) / 2;
	auto [leftMax, leftMin] = MaxMinNum(index * 2, left, mid, start, end);
	auto [rightMax, rightMin] = MaxMinNum(index * 2 + 1, mid + 1, right, start, end);
	return make_pair(max(leftMax, rightMax), min(leftMin, rightMin));

}
