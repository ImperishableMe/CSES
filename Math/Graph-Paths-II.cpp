#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 102; 

using T = long long;
const ll INF = 4e18;

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
                a[i][j] = (i == j)? 0: INF;
    }

    Matrix operator*(const Matrix &rhs) const {
        assert(C == rhs.R);
        Matrix res(R, rhs.C);
        res.set_infinity();
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                for (int k = 0; k < rhs.C; k++) {
                    if (a[i][j] == INF || rhs.a[j][k] == INF) continue;
                    res.a[i][k] = min(res.a[i][k], a[i][j] + rhs.a[j][k]);
                }
            }
        }
        return res;
    }

    void set_infinity(){
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) a[i][j] = INF;
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
    G.set_infinity();
    for (int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        G.a[a][b] = min(G.a[a][b], 1LL*c);
    }
    return G;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	Matrix G = create_matrix();

    G = bigmod(G, k);
    ll v = G.a[0][n-1];
    cout << ((v >= INF)?-1: v) << "\n";

	return 0;
}