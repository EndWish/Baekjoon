#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, m;
vector<int> nums;
vector<pii> anses;
vector<tuple<int, int, int*>> cmds;

vector<pii> matching;

vector<int> segTree;

int Compression(int num);
void Push(int index, int start, int end, int num);
int GetNum(int index, int start, int end, int left, int right);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	segTree.assign(n * 4 + 1, {});
	nums.assign(n + 1, {});
	matching.assign(n + 1, {});

	for (int i = 1; i <= n; ++i) {
		cin >> nums[i];
		matching[i].first = nums[i];
	}
	ranges::sort(matching);
	for (int i = 0; i <= n; ++i) {
		matching[i].second = i;
	}
	
	cin >> m;
	anses.assign(m, {});
	for (int i = 0; i < m; ++i) {
		int s, e, k;
		cin >> s >> e >> k;
		k = Compression(k);
		if (s - 1 == 0)
			anses[i].first = 0;
		else
			cmds.emplace_back(s - 1, k, &anses[i].first);
		cmds.emplace_back(e, k, &anses[i].second);
	}
	ranges::sort(cmds, [](const auto& a, const auto& b) {
		return get<0>(a) < get<0>(b);
		});

	//
	int cmdsIndex = 0;
	for (int i = 1; i <= n; ++i) {
		Push(1, 1, n, Compression(nums[i]));

		while (cmdsIndex < cmds.size() && get<0>(cmds[cmdsIndex]) == i) {
			*get<2>(cmds[cmdsIndex]) = GetNum(1, 1, n, get<1>(cmds[cmdsIndex]) + 1, n);
			++cmdsIndex;
		}
	}

	for (int i = 0; i < m; ++i) {
		cout << anses[i].second - anses[i].first << "\n";
	}

}

int Compression(int num) {
	auto it = ranges::upper_bound(matching, num, less<int>{}, & pii::first);
	--it;
	return it->second;
}

void Push(int index, int start, int end, int num) {
	if (start == end) {
		++segTree[index];
		return;
	}

	int mid = (start + end) / 2;
	if (start <= num && num <= mid) {
		Push(index * 2, start, mid, num);
	}
	else {
		Push(index * 2 + 1, mid + 1, end, num);
	}
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

int GetNum(int index, int start, int end, int left, int right) {
	if (right < left)
		return 0;

	// 범위 밖일 경우
	if (end < left || right < start)
		return 0;

	// 범위 안일 경우
	if (left <= start && end <= right)
		return segTree[index];

	// 범위에 걸치는 경우
	int mid = (start + end) / 2;
	return	  GetNum(index * 2, start, mid, left, right) 
			+ GetNum(index * 2 + 1, mid + 1, end, left, right);
	
}
