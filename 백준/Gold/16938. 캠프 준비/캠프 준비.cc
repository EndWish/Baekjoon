#include <iostream>
#include <array>

#define MAXN 15

using namespace std;

int n, l, r, x;
array<int, MAXN> arr;
int ans = 0;

void DFS(int index, int sum, int min, int max);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> l >> r >> x;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	//문제해결
	DFS(0, 0, 1000'000, 1);
	
	//출력
	cout << ans;

}

void DFS(int index, int sum, int min, int max) {
	if (index == n) {	// 모두 선택완료했을 경우
		if(l <= sum &&  sum <= r && x <= max - min)
			++ans;
		return;
	}

	DFS(index + 1, sum, min, max);

	DFS(index + 1, sum + arr[index], std::min(min, arr[index]), std::max(max, arr[index]));
}
