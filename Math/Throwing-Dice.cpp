#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 6;

using T = long long;

struct Matrix {
    int R, C;
    T a[N][N];

    Matrix(int n) : R(n), C(n) {
        assert(n <= N);
        memset(a, 0, sizeof(a));
    }
    Matrix(int r, int c) : R(r), C(c) {
        assert(r <= N && c <= N);
        memset(a, 0, sizeof(a));
    }

    void set_identity() {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                a[i][j] = i == j;
    }

    Matrix operator*(const Matrix &rhs) const {
        assert(C == rhs.R);
        Matrix res(R, rhs.C);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                for (int k = 0; k < rhs.C; k++) {
                    res.a[i][k] += a[i][j] * rhs.a[j][k] % M;
                    // res.a[i][j] += a[i][k] * rhs.a[k][j]
                    if (res.a[i][k] >= M)
                        res.a[i][k] -= M;
                }
            }
        }
        return res;
    }
};

ostream &operator<<(ostream &os, const Matrix &rhs) {
    for (int i = 0; i < rhs.R; i++) {
        for (int j = 0; j < rhs.C; j++) {
            os << rhs.a[i][j] << " \n"[j + 1 == rhs.C];
        }
    }
    return os;
}

Matrix bigmod(Matrix a, ll b) {
    assert(a.R == a.C);
    Matrix ans(a.R);
    ans.set_identity();
    Matrix po = a;
    while (b) {
        if (b & 1)
            ans = (ans * po);
        po = po * po;
        b >>= 1;
    }
    return ans;
}

Matrix create_matrix(){
	Matrix m(6, 6);
	for (int i = 0; i < 6; i++){
		m.a[0][i] = 1;
	}	
	for (int i = 0; i < 5; i++) m.a[i+1][i] = 1;
	return m;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	Matrix m = create_matrix();
	ll n;
	cin >> n;
	m = bigmod(m, n);
	cout << m.a[0][0] << "\n";
	return 0;
}