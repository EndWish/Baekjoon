#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

struct Log {
	int x1, x2;
	int number;
};

int n, q;
vector<Log> logs;
array<int, 100'001> parents;

int Find(int x);
void Unite(int a, int b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> q;

	logs.assign(n, {});
	int buffer = 0;
	for (int i = 0; i < n; ++i) {
		cin >> logs[i].x1 >> logs[i].x2 >> buffer;
		logs[i].number = i + 1;
	}

	iota(parents.begin(), parents.end(), 0);
	
	// 정렬을 통해 Unite횟수를 줄인다.
	ranges::sort(logs, less<int>{}, & Log::x1);

	int end = -1;
	for (int i = 0; auto [x1, x2, number] : logs) {
		// 겹치지 않을 경우
		if (end < x1) {
			end = x2;
		}
		// 겹칠 경우
		else {
			end = max(end, x2);
			Unite(number, logs[i - 1].number);
		}
		++i;
	}

	int a, b;
	for (int i = 0; i < q; ++i) {
		cin >> a >> b;
		if (Find(a) == Find(b)) {
			cout << 1 << "\n";
		}
		else {
			cout << 0 << "\n";
		}
	}

}

int Find(int x) {
	if (x == parents[x])
		return x;
	return parents[x] = Find(parents[x]);
}

void Unite(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a > b)
		swap(a, b);

	parents[b] = a;
}
