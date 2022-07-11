#include <iostream>
#include <array>
#include <numeric>

#define MAXN 100001

using namespace std;

int g, p;
array<int, MAXN> parent;

int Find(int x);
void Union(int a, int b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> g >> p;
	iota(parent.begin(), parent.end(), 0);

	//문제해결
	int ans = 0;
	bool stop = false;
	
	int input;
	for (int i = 0; i < p; ++i) {
		cin >> input;
		if (stop)
			continue;

		int find = Find(input);
		if (find == 0) {
			stop = true;
		}
		else {
			++ans;
			Union(find, find - 1);
		}

	}

	//출력
	cout << ans;
}

int Find(int x) {
	if (parent[x] == x)
		return x;
	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a < b)
		parent[b] = a;
	else
		parent[a] = b;
}