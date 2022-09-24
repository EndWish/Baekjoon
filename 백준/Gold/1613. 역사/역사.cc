#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
//#include <numeric>
//#include <format>

#define MAXN 401
#define MAXE 10

using namespace std;

int n, k, s;
int edge[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	int a, b;
	for (int i = 0; i < k; ++i) {
		cin >> a >> b;
		edge[a][b] = -1;
		edge[b][a] = 1;
	}

	//문제해결
	for (int via = 1; via <= n; ++via) {
		for (int s = 1; s <= n; ++s) {
			if (via == s || edge[s][via] == 0)
				continue;
			for (int e = s + 1; e <= n; ++e) {
				if (via == e || s == e || edge[via][e] == 0)
					continue;

				if (edge[s][via] == edge[via][e]) {
					edge[s][e] = edge[s][via];
					edge[e][s] = -edge[s][e];
				}
			}
		}
	}

	//출력
	cin >> s;
	for (int i = 0; i < s; ++i) {
		cin >> a >> b;
		cout << edge[a][b] << "\n";
	}

}