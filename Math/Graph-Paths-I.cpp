#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 102; 

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

ll n, m, k;
Matrix create_matrix(){
    cin >> n >> m >> k;

    Matrix G(n);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        G.a[a][b]++;
    }
    return G;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	Matrix G = create_matrix();

    G = bigmod(G, k);
    cout << G.a[0][n-1] << "\n";

	return 0;
}