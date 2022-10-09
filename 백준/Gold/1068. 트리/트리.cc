#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 50

int n;
vector<int> children[MAXN];
int parent[MAXN];
int deleteNode, root;

int GetLeafNode(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;

		parent[i] = input;
		if (input == -1)
			root = i;
		else
			children[input].push_back(i);
	}

	cin >> deleteNode;

	//문제해결
	cout << GetLeafNode(root);

	//출력

}

int GetLeafNode(int node) {
	if (node == deleteNode)
		return 0;

	int result = 0;
	for (int child : children[node]) {
		result += GetLeafNode(child);
	}

	return max(result, 1);
}
