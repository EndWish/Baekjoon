#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, m;
vector<vector<int>> children;
vector<int> segTree, salary;
vector<pii> childrenIndexRange;

int SetToEmployee(int offset, int employee);
void Change(int index, int start, int end, int left, int right, int add);
int GetExtraSalary(int index, int start, int end, int pos);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	children.assign(n + 1, {});
	salary.assign(n + 1, {});
	childrenIndexRange.assign(n + 1, {});
	segTree.assign(n * 4 + 1, {});

	cin >> salary[1];
	for (int i = 2; i <= n; ++i) {
		int parent;
		cin >> salary[i] >> parent;
		children[parent].push_back(i);
	}

	SetToEmployee(1, 1);

	for (int i = 0; i < m; ++i) {
		int a, x;

		char cmd;
		cin >> cmd;
		if (cmd == 'p') {
			cin >> a >> x;
			auto [s, e] = childrenIndexRange[a];
			if (s <= e) {
				Change(1, 1, n, s, e, x);
			}
		}
		else {
			cin >> a;
			cout << salary[a] + GetExtraSalary(1, 1, n, childrenIndexRange[a].second + 1) << "\n";
		}
	}

}

int SetToEmployee(int offset, int employee) {
	int result = 0;
	for (int child : children[employee]) {
		result += SetToEmployee(offset + result, child);
	}

	childrenIndexRange[employee] = { offset, offset + result - 1 };
	++result;
	return result;
}

void Change(int index, int start, int end, int left, int right, int add) {

	// 범위 밖일 경우
	if (end < left || right < start)
		return;

	// 범위 안일 경우
	if (left <= start && end <= right) {
		segTree[index] += add;
		return;
	}

	// 범위에 걸칠 경우
	int mid = (start + end) / 2;
	Change(index * 2, start, mid, left, right, add);
	Change(index * 2 + 1, mid + 1, end, left, right, add);

}

int GetExtraSalary(int index, int start, int end, int pos) {
	// update
	if (segTree[index] != 0 && start < end) {
		segTree[index * 2] += segTree[index];
		segTree[index * 2 + 1] += segTree[index];
		segTree[index] = 0;
	}

	if (start == end) {	// (== pos)
		return segTree[index];
	}

	int mid = (start + end) / 2;
	if (start <= pos && pos <= mid) {
		return GetExtraSalary(index * 2, start, mid, pos);
	}
	else {
		return GetExtraSalary(index * 2 + 1, mid + 1, end, pos);
	}
}
