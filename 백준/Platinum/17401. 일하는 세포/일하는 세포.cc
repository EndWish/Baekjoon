#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MOD 1'000'000'007
#define ll long long

using namespace std;

class Mat {
public:
	int r, c;
	vector<vector<ll>> mat;

	Mat(int _r, int _c) : r{ _r }, c{ _c } {
		mat.assign(r, vector<ll>(c, 0));
	}

	static Mat Idle(int _r) {
		Mat result(_r, _r);
		for (int i = 0; i < _r; ++i) {
			result.mat[i][i] = 1;
		}
		return result;
	}

	Mat operator*(const Mat& rhs) {
		Mat result(r, rhs.c);
		for (int x = 0; x < rhs.c; ++x) {
			for (int y = 0; y < r; ++y) {
				for (int z = 0; z < c; ++z) {
					result.mat[y][x] += (mat[y][z] * rhs.mat[z][x]) % MOD;
					result.mat[y][x] %= MOD;
				}
			}
		}
		return result;
	}
	Mat Pow(ll p) {
		// p == 0 일때는 단위행렬 리턴
		if (p == 0) {
			return Idle(r);
		}

		if (p == 1) {
			return *this;
		}

		if (p & 1) {	// 홀수 일경우
			return ((*this)* (*this)).Pow(p / 2) * (*this);
		}
		else {	// 짝수
			return ((*this) * (*this)).Pow(p / 2);
		}
	}
};

int t, n, d;
vector<Mat> matrix;	// mat[time%t][r][c]	// time%t 번째 행렬(지도)에서 

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> t >> n >> d;
	matrix.assign(t, Mat(n, n));

	int a, b, c, m;
	for (int i = 0; i < t; ++i) {
		cin >> m;
		for (int j = 0; j < m; ++j) {
			cin >> a >> b >> c;
			--a;
			--b;
			matrix[i].mat[a][b] = c;
		}
	}

	Mat tMatrix = Mat::Idle(n);	// 1~t번째 행렬을 순서대로 모두 곱한 행렬
	for (int i = 0; i < t; ++i) {
		tMatrix = tMatrix * matrix[i];
	}

	//문제해결
	for (int start = 0; start < n; ++start) {
		Mat row(1, n);
		row.mat[0][start] = 1;

		Mat result = tMatrix.Pow(d / t);
		for (int i = 0; i < d % t; ++i) {
			result = result * matrix[i];
		}
		result = row * result;

		for (int i = 0; i < n; ++i) {
			cout << result.mat[0][i] << " ";
		}
		cout << "\n";
	}

	//출력
	
}