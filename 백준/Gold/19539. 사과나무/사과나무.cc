#include <iostream>
#include <vector>

using namespace std;


int n;
vector<int> trees;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	trees.assign(n, {});
	for (int& tree : trees)
		cin >> tree;

	//문제해결
	int one = 0 , two = 0;
	for (int tree : trees) {
		two += tree / 2;
		one += tree % 2;
	}

	//출력
	if (((one + two * 2) % 3 == 0) && one <= two) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

}

