#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int n, m;
vector<int> arr;

bool MakeBluRay(int capacity);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	arr.assign(n, 0);
	for (int& a : arr)
		cin >> a;

	//문제해결
	int s = 0, e = 100'000 * 10'000;
	while (s < e) {
		int mid = (s + e) / 2;

		if (MakeBluRay(mid)) {
			e = mid;
		}
		else {
			s = mid + 1;
		}
	}

	//출력
	cout << s;

}

bool MakeBluRay(int capacity) {
	int bluRayCnt = 1;
	int curCapacity = 0;
	for (int a : arr) {
		if (capacity < a)	// 강의용량이 블루레이보다 클 경우 False
			return false;

		curCapacity += a;
		if (capacity < curCapacity) {	//용량을 초과 했을경우
			//다음 블루레이 사용
			++bluRayCnt;	
			curCapacity = a;

			if (m < bluRayCnt) {	// 가지고 있는 블루레이 개수를 초과할 경우
				return false;
			}
		}
	}

	return true;
}
