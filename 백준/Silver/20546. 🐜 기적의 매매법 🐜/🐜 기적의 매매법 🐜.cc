#include <iostream>
#include <vector>
#include <algorithm>

// 20546

using namespace std;

int money;
vector<int> stockPrice(14);

pair<int, int> BNP(int cash);
pair<int, int> TIMING(int cash);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> money;
	for (int& n : stockPrice)
		cin >> n;

	//문제해결
	pair<int, int> bnp = BNP(money);
	pair<int, int> timing = TIMING(money);
	
	int bnpMoney = bnp.first * stockPrice[13] + bnp.second;
	int timingMoney = timing.first * stockPrice[13] + timing.second;

	//출력
	if (bnpMoney < timingMoney)
		cout << "TIMING";
	else if (bnpMoney > timingMoney)
		cout << "BNP";
	else
		cout << "SAMESAME";

}

pair<int,int> BNP(int cash) {
	int stockN = 0;
	for (int i = 0; i < 14; ++i) {
		stockN += cash / stockPrice[i];
		cash %= stockPrice[i];
	}

	return { stockN, cash };
}

pair<int, int> TIMING(int cash) {
	int stockN = 0;

	int strait = 0;
	for (int i = 1; i < 14; ++i) {
		if (stockPrice[i - 1] < stockPrice[i])
			strait = max(strait + 1, 1);
		else if(stockPrice[i - 1] > stockPrice[i])
			strait = min(strait - 1, -1);

		if (strait == 3) {	// 3일 연속 올랐을 경우
			cash += stockN * stockPrice[i]; // 풀매도
			stockN = 0;
		}
		else if (strait == -3) {
			stockN += cash / stockPrice[i];	// 풀매수
			cash %= stockPrice[i];
		}
	}

	return { stockN, cash };
}
