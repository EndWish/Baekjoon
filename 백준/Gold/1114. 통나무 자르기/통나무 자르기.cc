#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int l, k, c;
vector<int> cuts;

pair<bool, int> CanCut(int leng);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> l >> k >> c;
	cuts.assign(k, {});
	for (int& cut : cuts)
		cin >> cut;

	cuts.push_back(0);
	cuts.push_back(l);
	ranges::sort(cuts);
	ranges::unique(cuts);

	int s = 1, e = l;

	while (s != e) {
		int mid = (s + e) / 2;
		if (CanCut(mid).first) {
			e = mid;
		}
		else {
			s = mid + 1;
		}
	}

	cout << s << " " << CanCut(s).second;
}

pair<bool, int> CanCut(int leng) {
	int cutCount = 0;
	int prevCutPos = l;
	for (int i = cuts.size() - 2; 0 <= i; --i) {
		int cut = cuts[i];


		// 통나무의 길이가 leng보다 길어지면 이전의 자를 수 있는 위치에서 자른다.
		if (leng < prevCutPos - cut) {
			if (leng < cuts[i + 1] - cut)	// 파츠가 leng보다 클경우
				return  { false, -1 };

			if (prevCutPos == cuts[i + 1]) {	// 자를 수 있는 위치가 없을 경우
				return { false, -1 };
			}

			prevCutPos = cuts[i + 1];
			++cutCount;
		}
	}

	// 자를 수 있는 횟수를 넘길 경우
	if (c < cutCount) {
		return { false, -1 };
	}

	return { true, cutCount < c ? cuts[1] : prevCutPos};
}
