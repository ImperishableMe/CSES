#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 2e6 + 10;

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


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;

	vector<ll> dp(n+2, 0);
	dp[1] = 0;
	dp[2] = 1;

	for (int i = 3; i <= n; i++){
		dp[i] = (i-1)*(dp[i-1] + dp[i-2]) % M;
	}
	cout << dp[n] << "\n";
	return 0;
}