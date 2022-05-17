#include <iostream>
#include <array>
#include <numeric>

using namespace std;

int n;
array<int, 4> num;
array<bool, 1001> visit;

void SetNum(int index, int remains);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;

	//문제해결
	SetNum(0, n);
	
	//출력
	cout << count(visit.begin(), visit.end(), true);

}

void SetNum(int index, int remains) {
	if (index == 3) {
		num[index] = remains;

		int sum = num[0] + num[1] * 5 + num[2] * 10 + num[3] * 50;
		visit[sum] = true;
		return;
	}

	for (int i = 0; i <= remains; ++i) {
		num[index] = i;
		SetNum(index + 1, remains - i);
	}

}
