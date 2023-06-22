#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

struct Student {
	int number;
	array<int, 3> rank;
};

int n;
vector<Student> students;
vector<int> segTree;

int GetRankInSegTree(int index, int start, int end, int left, int right);
void PushInSegTree(int index, int start, int end, int pos, int value);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	students.assign(n, {});
	segTree.assign(n * 4 + 1, INF);

	for (int i = 0; i < n; ++i)
		students[i].number = i + 1;

	for (int i = 0; i < 3; ++i) {
		for (int rank = 1; rank <= n; ++rank) {
			int number;
			cin >> number;
			students[number - 1].rank[i] = rank;
		}
	}
	
	ranges::sort(students, [](Student& a, Student& b) {
		return a.rank[0] < b.rank[0];
		});
	
	int ans = 0;
	for (auto& student : students) {
		// 1. 세그먼트 트리에 있다는 것은 나보다 첫번째 시험의 등수가 높다는 의미
		// 2. 세그먼트 트리에서 "두번째 등수의 인덱스"보다 앞쪽 구간에 있다는것은 두번째 시험의 등수가 높다는 의미
		// 3. 세그먼트 트리의 구간에서 최소값이 내보다 높다는 의미는 세번째 시험에서 나보다 등수가 높다는 의미
		if (student.rank[2] < GetRankInSegTree(1, 1, n, 1, student.rank[1])) {
			++ans;
		}
		
		PushInSegTree(1, 1, n, student.rank[1], student.rank[2]);
	}

	cout << ans;
}

int GetRankInSegTree(int index, int start, int end, int left, int right) {
	// 범위 밖일 경우
	if (end < left || right < start)
		return INF;

	// 범위 안일 경우
	if (left <= start && end <= right)
		return segTree[index];

	// 범위에 걸치는 경우
	int mid = (start + end) / 2;
	return min(	GetRankInSegTree(index * 2, start, mid, left, right),
				GetRankInSegTree(index * 2 + 1, mid + 1, end, left, right));
}

void PushInSegTree(int index, int start, int end, int pos, int value) {

	if (start == end) {	// (== pos)
		segTree[index] = value;
		return;
	}

	int mid = (start + end) / 2;
	if (start <= pos && pos <= mid) {
		PushInSegTree(index * 2, start, mid, pos, value);
	}
	else {
		PushInSegTree(index * 2 + 1, mid + 1, end, pos, value);
	}

	segTree[index] = min(segTree[index * 2], segTree[index * 2 + 1]);
}
