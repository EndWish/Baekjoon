#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

struct Cmd {
	int left, right, index;
};

int n, m;
vector<int> nums;
array<int, 1'000'001> cnt;
int cntSize = 0;
vector<Cmd> cmds;
vector<int> anses;

void addCount(int num);
void subCount(int num);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	cin >> m;
	anses.assign(m, {});
	for (int index = 0; index < m; ++index) {
		int i, j;
		cin >> i >> j;
		cmds.emplace_back(i - 1, j - 1, index);
	}

	int sqrtN = sqrt(n);
	ranges::sort(cmds, [sqrtN](const Cmd& a, const Cmd& b) {
		if (a.left / sqrtN == b.left / sqrtN)
			return a.right < b.right;
		return a.left / sqrtN < b.left / sqrtN;
		});

	// 첫번째 명령 수행
	int curLeft = cmds[0].left, curRight = cmds[0].right;
	for (int i = curLeft; i <= curRight; ++i)
		addCount(nums[i]);
	anses[cmds[0].index] = cntSize;

	for (int i = 1; i < m; ++i) {
		while (curLeft < cmds[i].left)
			subCount(nums[curLeft++]);
		
		while (cmds[i].left < curLeft)
			addCount(nums[--curLeft]);

		while (curRight < cmds[i].right)
			addCount(nums[++curRight]);

		while (cmds[i].right < curRight)
			subCount(nums[curRight--]);

		anses[cmds[i].index] = cntSize;
	}

	for (int ans : anses)
		cout << ans << "\n";

}

void addCount(int num) {
	if (cnt[num] == 0)
		++cntSize;
	++cnt[num];
}

void subCount(int num) {
	--cnt[num];
	if (cnt[num] == 0)
		--cntSize;
}

