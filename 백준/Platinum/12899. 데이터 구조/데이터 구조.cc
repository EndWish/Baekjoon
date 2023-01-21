#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

#define pii pair<int,int>
#define MAXN 2'000'000

int n;
array<int, MAXN * 4 + 1> seg;

void AddNum(int index, int start, int end, int pos);
int DeleteNum(int index, int start, int end, int numberth);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int cnt = 1;

	//문제해결
	for (int i = 0; i < n; ++i) {
		int t, x;
		cin >> t >> x;
		if (t == 1) {
			AddNum(1, 1, MAXN, x);
		}
		else if (t == 2) {
			cout << DeleteNum(1, 1, MAXN, x) << "\n";
		}

	}

}

void AddNum(int index, int start, int end, int num) {
	if (start == end) {
		++seg[index];
		return;
	}

	int mid = (start + end) / 2;
	if (start <= num && num <= mid)
		AddNum(index * 2, start, mid, num);
	else
		AddNum(index * 2 + 1, mid + 1, end, num);

	seg[index] = seg[index * 2] + seg[index * 2 + 1];
}

int DeleteNum(int index, int start, int end, int numberth) {
	if (start == end) {
		--seg[index];
		return start;
	}

	int result;
	int mid = (start + end) / 2;
	if (numberth <= seg[index * 2])
		result = DeleteNum(index * 2, start, mid, numberth);
	else
		result = DeleteNum(index * 2 + 1, mid + 1, end, numberth - seg[index * 2]);

	seg[index] = seg[index * 2] + seg[index * 2 + 1];
	return result;
}
