#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>

#define lli long long int

using namespace std;

int n, m;
pair<lli, lli> v[1001];
int parent[1001];

int Find(int x);
void Unite(int a, int b);
bool IsUnion(int a, int b);

lli Dist2(lli dx, lli dy);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL);

	//입력받기 & 최기화
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> v[i].first >> v[i].second;
		parent[i] = i;
	}

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		Unite(a, b);
	}

	//문제해결
	vector<tuple<lli, int, int>> pq;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (!IsUnion(i, j)) {
				lli dist2 = Dist2(v[i].first - v[j].first, v[i].second - v[j].second);
				pq.push_back({ dist2, i, j });
			}
		}
	}

	sort(pq.begin(), pq.end());

	double ans = 0;
	for (int i = 0; i < pq.size(); ++i) {
		lli dist2 = get<0>(pq[i]);
		int v1 = get<1>(pq[i]);
		int v2 = get<2>(pq[i]);

		if (IsUnion(v1, v2)) {
			continue;
		}

		ans += sqrt(dist2);
		Unite(v1, v2);

	}

	//출력하기
	cout.precision(2);
	cout << fixed << ans;

	return 0;
}

int Find(int x) {
	if (parent[x] == x) {
		return x;
	}

	parent[x] = Find(parent[x]);
	return parent[x];
}

void Unite(int a, int b) {
	int aPar = Find(a);
	int bPar = Find(b);

	if (aPar < bPar) {
		parent[bPar] = aPar;
	}
	else {
		parent[aPar] = bPar;
	}
}

bool IsUnion(int a, int b) {
	if (Find(a) == Find(b)) {
		return true;
	}
	return false;
}

lli Dist2(lli dx, lli dy) {
	return dx * dx + dy * dy;
}
