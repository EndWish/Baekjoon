#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n, m;
int CutNum(int sausage, int people);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//초기화,입력값 받기
	cin >> n >> m;

	//문제해결
	cout << CutNum(n, m);

	//출력



}

int CutNum(int sausage, int people) {
	if (people == 1 || people == 0)	// 한사람이 전부 먹을 경우 or 먹을 사람이 없을 경우(이미 소세지를 다 나누어 가진 경우)
		return 0;

	sausage %= people;
	if (sausage == 0)	// 딱맞게 떨어질 경우
		return 0;

	int cutting = 0;
	cutting += (people - 1) / sausage * sausage;	// people % sausage == 0 ? people - sausage : people; 와 같다.
	cutting += CutNum(sausage, people % sausage);
	return cutting;
}