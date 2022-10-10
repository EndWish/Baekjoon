#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 100'001
#define INF numeric_limits<int>::max()

int n, m;
vector<int> nums;
vector<int> segTree;

void MakeSegTree(int index, int left, int right);
int FindMinValue(int index, int left, int right, int start, int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	nums.assign(n + 1, {});
	segTree.assign(4 * n + 1, {});

	for (int& num : nums | views::drop(1))
		cin >> num;

	//문제해결
	MakeSegTree(1, 1, n);

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		cout << FindMinValue(1, 1, n, a, b) << "\n";
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
	segTree[index] = min(segTree[index * 2], segTree[index * 2 + 1]);
}

int FindMinValue(int index, int left, int right, int start, int end) {
	// 범위밖인 경우
	if (right < start || end < left)
		return INF;

	// 범위안인 경우
	if (start <= left && right <= end)
		return segTree[index];

	// 걸치는 경우
	int mid = (left + right) / 2;
	int lvalue = FindMinValue(index * 2, left, mid, start, end);
	int rvalue = FindMinValue(index * 2 + 1, mid + 1, right, start, end);
	return min(lvalue, rvalue);

}
