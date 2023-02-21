#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define MOD 1'000'003LL

class Matrix {
public:
	static Matrix Identity(int _size);

private:
	ll row, col;
	vector<vector<ll>> mat;

public:
	Matrix();
	Matrix(ll _row, ll _col);
	Matrix(ll _row, ll _col, vector<ll>& _init);

	Matrix operator*(const Matrix& other);
	Matrix Pow(ll _p);

	void SetNum(ll _row, ll _col, ll _num);
	ll GetNum(ll _row, ll _col);

	void Print();
};

ll n, s, e, t;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> s >> e >> t;
	--s;	// 정점을 zero-base로 바꾼다.
	--e;
	
	//문제해결

	// 1. 초기상태를 나타내는 백터를 만든다.
	vector<ll> nums(n * 5, 0);
	nums[s] = 1;
	Matrix vec(1, n * 5, nums);

	// 2. 행렬을 만든다.
	Matrix mat(n * 5, n * 5);
	for (int preNode = 0; preNode < n; ++preNode) {
		for (int nextNode = 0; nextNode < n; ++nextNode) {
			char dist;
			cin >> dist;
			dist -= '0';
			if(dist != 0)
				mat.SetNum(preNode + n * (dist - 1), nextNode, 1);
		}
	}
	for (int i = n; i < n * 5; ++i) {
		mat.SetNum(i - n, i, 1);
	}

	//vec.Print();
	//mat.Print();

	// 3. 벡터와 행렬의 제곱을 이용하여 값을 구한다.
	Matrix ans = vec * mat.Pow(t);
	cout << ans.GetNum(0, e);

}

Matrix Matrix::Identity(int _size) {
	Matrix matrix(_size, _size);
	for (int i = 0; i < _size; ++i)
		matrix.mat[i][i] = 1;

	return matrix;
}

Matrix::Matrix() {
	row = 0;
	col = 0;
}

Matrix::Matrix(ll _row, ll _col) {
	row = _row;
	col = _col;
	mat.assign(row, vector<ll>(col, 0));
}

Matrix::Matrix(ll _r, ll _c, vector<ll>& _init) : Matrix(_r, _c) {
	auto it = _init.begin();
	for (ll r = 0; r < row; ++r) {
		for (ll c = 0; c < col; ++c) {
			mat[r][c] = *it % MOD;
			++it;
		}
	}
}

Matrix Matrix::operator*(const Matrix& other) {
	if (col != other.row) {
		cout << "에러 : 크기가 맞지 않아 곱셈을 할 수 없다.\n";
		return Matrix();
	}

	Matrix matrix(row, other.col);
	for (ll r = 0; r < row; ++r) {
		for (ll c = 0; c < other.col; ++c) {
			for (ll d = 0; d < col; ++d) {
				matrix.mat[r][c] += mat[r][d] * other.mat[d][c];
				matrix.mat[r][c] %= MOD;
 			}
		}
	}

	return matrix;
}

Matrix Matrix::Pow(ll _p) {
	if (_p == 0) {
		if (col != row)
			cout << "행과 열의 크기가 같지 않아 단위행렬을 반환할 수 없습니다.\n";
		return Matrix::Identity(col);
	}
	else if (_p == 1) {
		return *this;
	}

	Matrix& me = *this;

	if (_p & 1) {	// 홀수일 경우
		return (me * me).Pow(_p / 2) * me;
	}
	else {	//짝수일 경우
		return (me * me).Pow(_p / 2);
	}

}

void Matrix::SetNum(ll _row, ll _col, ll _num) {
	mat[_row][_col] = _num;
}

ll Matrix::GetNum(ll _row, ll _col) {
	return mat[_row][_col];
}

void Matrix::Print() {
	cout << "-------------------------------\n";
	for (int r = 0; r < row; ++r) {
		for (int c = 0; c < col; ++c) {
			cout << mat[r][c] << " ";
		}
		cout << "\n";
	}
}

