#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 4001

class Node {
public:
	Node() {};

	int stack = 0;
	unordered_map<char, Node*> next;

	Node* GetNext(char ch) {
		if (!next.contains(ch)) {
			Node* pNode = new Node();
			next[ch] = pNode;
		}
		return next[ch];
	}
};

int n;
string s, t;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	Node startNode;

	cin >> n;
	string word;
	int count;
	int maxCount = 0;
	

	for (int i = 0; i < n; ++i) {
		Node* pNode = &startNode;
		count = 0;

		cin >> word;
		
		// 예외 처리
		if (i == 0)
			s = word;
		else if (i == 1)
			t = word;

		// 트라이 구조를 탐색 및 삽입
		for (int j = 0; char ch : word) {
			pNode = pNode->GetNext(ch);	// 없으면 알아서 생긴다.
			++pNode->stack;

			if (2 <= pNode->stack)
				++count;

			// 최고 기록 갱신
			if (maxCount < count) {
				maxCount = count;
				string tempS = word.substr(0, j + 1);

				Node* pTempNode = pNode;
				while (true) {
					auto nextIt = pTempNode->next.begin();
					if (nextIt != pTempNode->next.end()) {
						tempS.push_back(nextIt->first);
						pTempNode = nextIt->second;
					}
					else
						break;
				}
				s = tempS;
				t = word;
			}

			++j;
		}
	}

	cout << s << "\n";
	cout << t << "\n";

}

