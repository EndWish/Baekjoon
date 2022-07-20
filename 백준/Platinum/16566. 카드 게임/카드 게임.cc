#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m, k;
vector<int> deck;
vector<int> parent;

int Find(int x);
void Unite(int a, int b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);	

	//최기화,입력값 받기
	cin >> n >> m >> k;

	// 1. 부모 초기화
	parent.assign(n + 1, 0);
	iota(parent.begin(), parent.end(), 0);

	// 2. 덱 설정
	deck.assign(m, 0);
	for (int& card : deck)
		cin >> card;
	ranges::sort(deck);

	//문제해결
	int opponentCard;
	for (int i = 0; i < k; ++i) {
		cin >> opponentCard;
		int pickCard = *ranges::upper_bound(deck, opponentCard);	// 민수가 카드를 내지 못하는 경우는 없으므로 end()일 수 없다.
		int pickCardParent = Find(pickCard);
		cout << pickCardParent << "\n";
		
		auto nextCardIt = ranges::lower_bound(deck, pickCardParent + 1);
		if (nextCardIt != deck.end()) {
			Unite(pickCardParent, *nextCardIt);
		}
	}

	//출력
	
}

int Find(int x) {
	if (x == parent[x])
		return x;
	return parent[x] = Find(parent[x]);
}

void Unite(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a < b)
		parent[a] = b;
	else
		parent[b] = a;
}
