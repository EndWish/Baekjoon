#include <iostream>
#include <vector>
#include <numeric>

#define ll long long

using namespace std;

int n;
vector<char> oper;
vector<ll>  num;
vector<bool> bracket;

ll ans = numeric_limits<ll>::min();

void DFS(int index);
ll Calculate();
ll arithmetic(ll a, ll b, char c);

void Print(vector<ll>& a, vector<pair<char, bool>>& b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;

	ll inputNum;
	char inputChar;
	for (int i = 0; i < n; ++i) {
		if (i & 1) {	// 홀수일 경우
			cin >> inputChar;
			oper.push_back(inputChar);
		}
		else {	//짝수일 경우
			cin >> inputNum;
			num.push_back(inputNum);
		}
	}

	bracket.assign(oper.size(), false);

	//문제해결
	DFS(0);
	
	//출력
	cout << ans;

}

void DFS(int index) {
	if (index == n / 2) {	// 결과 계산하기
		ans = std::max(ans, Calculate());
		return;
	}

	bracket[index] = false;
	DFS(index + 1);

	if (index == 0 || !bracket[index - 1]) {
		bracket[index] = true;
		DFS(index + 1);
	}

}

ll Calculate() {
	vector<ll> tempNum(num.begin(), num.end());
	vector<pair<char, bool>> tempOper(oper.size());
	for (int i = 0; i < tempOper.size(); ++i) {
		tempOper[i].first = oper[i];
		tempOper[i].second = bracket[i];
	}

	for (int i = 0; i < tempOper.size(); ++i) {
		if (tempOper[i].second) {
			tempNum[i + 1] = arithmetic(tempNum[i], tempNum[i + 1], tempOper[i].first);
			tempOper.erase(tempOper.begin() + i);
			tempNum.erase(tempNum.begin() + i);
			--i;
			//Print(tempNum, tempOper);
		}
		
	}

	while (!tempOper.empty()) {
		tempNum[1] = arithmetic(tempNum[0], tempNum[1], tempOper[0].first);
		tempOper.erase(tempOper.begin());
		tempNum.erase(tempNum.begin());
		//Print(tempNum, tempOper);
	}

	return tempNum[0];

}

void Print(vector<ll>& a, vector<pair<char, bool>>& b) {
	for (int i = 0; i < b.size(); ++i) {
		cout << a[i] << " " << b[i].first << " ";
	}
	cout << a[a.size() - 1] << "\n";
}

ll arithmetic(ll a, ll b, char c) {
	switch (c) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	default:
		break;
	}
}

