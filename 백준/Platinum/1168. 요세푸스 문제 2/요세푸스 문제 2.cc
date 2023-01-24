#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, k;
vector<int> seg;

void InitSeg(int index, int start, int end);
int Pop(int index, int start, int end, int numberth);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	seg.assign(n * 4 + 1, {});
	InitSeg(1, 1, n);

	//문제해결
	cout << "<";
	int numberth = 0;
	for (int i = 0; i < n; ++i) {
		numberth = (numberth + k - 1) % (n - i) + 1;

		cout << Pop(1, 1, n, numberth);
		if (i < n - 1)
			cout << ", ";

		--numberth;
	}
	cout << ">";
	
}

void InitSeg(int index, int start, int end) {
	if (start == end) {
		seg[index] = 1;
		return;
	}

	int mid = (start + end) / 2;
	InitSeg(index * 2, start, mid);
	InitSeg(index * 2 + 1, mid + 1, end);
	seg[index] = seg[index * 2] + seg[index * 2 + 1];
}
int Pop(int index, int start, int end, int numberth) {
	if (start == end) {
		seg[index] = 0;
		return start;
	}

	int result;
	int mid = (start + end) / 2;
	if (numberth <= seg[index * 2])
		result = Pop(index * 2, start, mid, numberth);
	else
		result = Pop(index * 2 + 1, mid + 1, end, numberth - seg[index * 2]);

	seg[index] = seg[index * 2] + seg[index * 2 + 1];
	return result;
}
