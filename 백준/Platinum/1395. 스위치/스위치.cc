#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

int n, m;
vector<int> segTree;
vector<bool> reversal;

void Update(int index, int start, int end);
void Change(int index, int start, int end, int left, int right);
int GetOn(int index, int start, int end, int left, int right);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	segTree.assign(n * 4 + 1, {});
	reversal.assign(n * 4 + 1, false);

	for (int i = 0; i < m; ++i) {
		int o, s, t;
		cin >> o >> s >> t;
		if (o == 0) {
			Change(1, 1, n, s, t);
		}
		else {
			cout << GetOn(1, 1, n, s, t) << "\n";
		}
	}


}

void Update(int index, int start, int end) {
	if (reversal[index]) {
		segTree[index] = (end - start + 1) - segTree[index];	// 값을 반전시킨다.
		if (start != end) {	// 리프노드가 아닐경우 자식노드에 반전을 전파
			reversal[index * 2] = !reversal[index * 2];
			reversal[index * 2 + 1] = !reversal[index * 2 + 1];
		}
		reversal[index] = false;
	}
}
void Change(int index, int start, int end, int left, int right) {
	Update(index, start, end);

	// 범위 밖일 경우
	if (end < left || right < start)
		return;

	// 범위 안일 경우
	if (left <= start && end <= right) {
		reversal[index] = !reversal[index];
		Update(index, start, end);
		return;
	}

	// 범위에 걸치는 경우
	int mid = (start + end) / 2;
	Change(index * 2, start, mid, left, right);
	Change(index * 2 + 1, mid + 1, end, left, right);
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];

}

int GetOn(int index, int start, int end, int left, int right) {
	Update(index, start, end);

	// 범위 밖일 경우
	if (end < left || right < start)
		return 0;

	// 범위 안일 경우
	if (left <= start && end <= right) {
		return segTree[index];
	}

	// 범위에 걸치는 경우
	int result = 0;
	int mid = (start + end) / 2;
	result += GetOn(index * 2, start, mid, left, right);
	result += GetOn(index * 2 + 1, mid + 1, end, left, right);
	return result;
}
