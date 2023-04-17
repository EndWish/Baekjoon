#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Node {
public:
	unordered_map<char, Node*> next;

	void Insert(const string str, int startIndex) {
		if (str.size() <= startIndex)
			return;

		char ch = str[startIndex];
		auto it = next.find(ch);
		if (it != next.end()) {
			it->second->Insert(str, startIndex + 1);
		}
		else {
			next[ch] = new Node();
			next[ch]->Insert(str, startIndex + 1);
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	Node root;

	string S, P;
	cin >> S;
	for (int i = 0; i < S.size(); ++i) {
		root.Insert(S, i);
	}

	cin >> P;
	int ans = 1;
	Node* pNode = &root;
	for (int i = 0; i < P.size(); ++i) {
		char ch = P[i];
		if (pNode->next.contains(ch)) {
			pNode = pNode->next[ch];
		}
		else {
			pNode = root.next[ch];
			++ans;
		}
	}

	cout << ans;
}

