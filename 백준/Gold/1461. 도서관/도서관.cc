#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;

vector<int> books1, books2;

vector<int> getDists(vector<int>& books);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int value;
		cin >> value;
		if (0 < value)
			books1.push_back(value);
		else
			books2.push_back(-value);
	}

	ranges::sort(books1);
	ranges::sort(books2);

	vector<int> dists1 = getDists(books1);
	vector<int> dists2 = getDists(books2);

	dists1.insert(dists1.end(), dists2.begin(), dists2.end());

	cout << reduce(dists1.begin(), dists1.end()) * 2 - *ranges::max_element(dists1);
	
}

vector<int> getDists(vector<int>& books) {
	vector<int> result;
	int index = books.size() - 1;
	while (0 <= index) {
		result.push_back(books[index]);
		int cnt = m;
		while (0 <= index && cnt > 0) {
			--index;
			--cnt;
		}
	}
	return result;
}
