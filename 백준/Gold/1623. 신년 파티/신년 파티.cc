#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

//1623

using namespace std;

int n;
vector<int> punk;
vector<vector<int>> tree;
vector<int> dp[2];

int DFS(int visit, int member);
void GetMembers(int visit, int member, vector<int>& out);
void PrintMember(vector<int>& members);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	punk.assign(n, 0);
	for (int& i : punk)
		cin >> i;
	
	tree.assign(n, vector<int>{});
	for (int i = 1; i < n; ++i) {
		int superior;
		cin >> superior;
		tree[superior - 1].push_back(i);	// zero-base 로 번호를 매김(사장이 0번)
	}

	for (int i = 0; i < 2; ++i)
		dp[i].assign(n, numeric_limits<int>::min());

	//문제해결
	cout << DFS(1, 0) << " ";
	cout << DFS(0, 0) << "\n";

	//출력
	vector<int> members;
	for (int i = 1; i >= 0; --i) {
		members.clear();
		GetMembers(i, 0, members);
		PrintMember(members);
	}

}

int DFS(int visit, int member) {
	if (dp[visit][member] != numeric_limits<int>::min())	// 이미 값을 구해 놓았다면
		return dp[visit][member];

	dp[visit][member] = 0;
	
	if (visit) {	// 해당 직원이 참석하는 경우
		dp[visit][member] += punk[member];
		
		for (int i : tree[member])	// 부하직원에 대해
			dp[visit][member] += DFS(0, i);	// 내가 참석했으니 부하직원은 참석하지 못함
	}
	else {	//참석하지 않는 경우
		
		for (int i : tree[member])	// 부하직원에 대해
			dp[visit][member] += max(DFS(0, i), DFS(1, i));
	}

	return dp[visit][member];
}

void GetMembers(int visit, int member, vector<int>& out) {
	if (visit) {
		out.push_back(member);
		for (int i : tree[member])
			GetMembers(0, i, out);
	}
	else {
		for (int i : tree[member]) {
			if (DFS(0, i) < DFS(1, i))
				GetMembers(1, i, out);
			else
				GetMembers(0, i, out);
		}

	}
}

void PrintMember(vector<int>& members) {
	ranges::sort(members);

	for (int i : members)
		cout << i + 1 << " ";
	cout << "-1\n";

}
