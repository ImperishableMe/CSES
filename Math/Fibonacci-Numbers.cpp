#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 2;

struct mat {
	ll a[N][N] = {{0,0}, {0,0}};
	void set_identity(){
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) a[i][j] = i == j;
	}
	mat operator*(const mat &rhs) const {
		mat res;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				for (int k = 0; k < N; k++){
					res.a[i][k] += a[i][j] * rhs.a[j][k] % M;
					// res.a[i][j] += a[i][k] * rhs.a[k][j] 
					if (res.a[i][k] >= M) res.a[i][k] -= M;
				}
			}
		}
		return res;
	}
};

ostream& operator<<(ostream &os, mat &rhs) {
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			os << rhs.a[i][j] << " \n"[j + 1 == N];
		}
	}	
	return os;
}


mat bigmod(mat a, ll b, int mod = M){
	mat ans;
	ans.set_identity();
	mat po = a;
	while (b){
		if (b&1) ans = (ans*po);
		po = po*po;
		b >>= 1;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);

	ll n;
	cin >> n;
	if (n == 0) {
		cout << "0\n"; return 0;
	}

	mat F;
	F.a[0][0] = F.a[0][1] = F.a[1][0] = 1;
	// cout << F << endl;
	F = bigmod(F, n-1);

	cout << F.a[0][0] << endl; 

	return 0;
}