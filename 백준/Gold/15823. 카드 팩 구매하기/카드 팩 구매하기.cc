#include <iostream>
#include <vector>
#include <array>

// 15823

using namespace std;

int n, m;
vector<int> v;
array<int, 500'001> visit;

bool MakeCardPack(int packNum);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	v.resize(n);
	for (int& element : v)
		cin >> element;

	//문제해결
	int s = 1; int e = n / m;
	while (s < e) {
		int mid = (s + e + 1) / 2;
		if (MakeCardPack(mid))
			s = mid;
		else
			e = mid - 1;
	}

	//출력
	cout << s;

}

bool MakeCardPack(int packNum) {
	visit.fill(-1);

	int cardPackNum = 0;
	int start = 0;
	int i = 0;
	while (start + packNum - 1 < n && cardPackNum < m) {	// m의 개 카드팩을 만들거나, 불가능할때 까지 반복
		
		bool makeSuccess = true;
		for (; i < start + packNum; ++i) {	// packNum묶음의 카드팩을 만들 수 있는지 확인
			if (visit[v[i]] < start) {	// 현재 팩에 포함되지 않은 카드일 경우
				visit[v[i]] = i;	// 포함시킨다.
			}
			else {	// 이미 포함되었던 카드라면
				start = visit[v[i]] + 1;	// 겹치는 카드 바로 다음부터 시작
				visit[v[i]] = i;	// 다음번에 확인확인할 카드팩에 포함
				++i;	// 위에서 포함시켰으니 break로 나가기 전에 ++i 해준다.
				makeSuccess = false;
				break;
			}
		}

		if (makeSuccess) {
			++cardPackNum;	// 만든 카드팩의 수++
			start = i;	// 새로운 카드팩의 시작위치 재설정
		}
	}

	if (cardPackNum == m) {	// m개의 카드팩을 만들었다면
		return true;
	}
	return false;

}

