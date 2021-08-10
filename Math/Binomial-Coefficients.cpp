#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 1e6 + 10;

ll fact[N], inv[N];

ll bigmod(ll a, ll b, ll mod = M){
	ll ans = 1, po = a;
	while (b){
		if (b&1) ans = (1LL*ans*po) % mod;
		po = (1LL*po*po) % mod;
		b >>= 1;
	}
	return ans;
}

ll ncr(int n, int r){
	if (n < 0 || r < 0 || n < r) return 0;
	return fact[n] * inv[r] % M * inv[n-r] % M;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);

	fact[0] = 1;
	for (int i = 1; i < N; i++) fact[i] = fact[i-1] * i % M;

	inv[N-1] = bigmod(fact[N-1], M-2);
	for (int i = N - 2; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % M;


	int q;
	cin >> q;
	while (q--){
		int a, b;
		cin >> a >> b;
		cout << ncr(a, b) << "\n";
	}

	return 0;
}