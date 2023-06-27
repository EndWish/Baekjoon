#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;
vector<int> nums;
vector<vector<int>> mergeTree;

void InitMergeTree();
void InitMergeTreeDFS(int index, int start, int end);
int Query(int index, int start, int end, int left, int right, int num);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n + 1, {});
	for (int& num : nums | views::drop(1))
		cin >> num;

	InitMergeTree();

	cin >> m;
	int lastAns = 0;
	for (int index = 0; index < m; ++index) {
		int a, b, c;
		cin >> a >> b >> c;
		a = a ^ lastAns;
		b = b ^ lastAns;
		c = c ^ lastAns;
		lastAns = Query(1, 1, n, a, b, c);
		cout << lastAns << "\n";
	}

}

void InitMergeTree() {
	mergeTree.assign(n * 4 + 1, {});
	InitMergeTreeDFS(1, 1, n);
}

void InitMergeTreeDFS(int index, int start, int end) {
	if (start == end) {
		mergeTree[index].push_back(nums[start]);
		return;
	}

	int mid = (start + end) / 2;
	InitMergeTreeDFS(index * 2, start, mid);
	InitMergeTreeDFS(index * 2 + 1, mid + 1, end);

	ranges::merge(mergeTree[index * 2], mergeTree[index * 2 + 1], back_inserter(mergeTree[index]));
	
}

int Query(int index, int start, int end, int left, int right, int num) {
	// 범위 밖
	if (end < left || right < start)
		return 0;

	// 범위 안
	if (left <= start && end <= right)
		return mergeTree[index].end() - ranges::upper_bound(mergeTree[index], num);

	// 범위에 걸침
	int mid = (start + end) / 2;
	return	  Query(index * 2, start, mid, left, right, num)
			+ Query(index * 2 + 1, mid + 1, end, left, right, num);


}
