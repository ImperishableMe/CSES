#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PII = pair<ll,ll>;

int const M = 1e9 + 7;

ll bigmod(ll a, ll b, ll mod = M){
	ll ans = 1, po = a;
	while (b){
		if (b&1) ans = (1LL*ans*po) % mod;
		po = (1LL*po*po) % mod;
		b >>= 1;
	}
	return ans;
}

inline ll modInv(ll a, ll mod = M){
	return bigmod(a, mod - 2);
}

ll NOD(vector<PII> &pf){
	ll ans = 1;
	for (auto [p, e]: pf) ans = ans * (e + 1) % M;
	return ans;
}

ll SOD(vector<PII> &pf){
	ll ans = 1;
	for (auto [p, e] : pf) {
		ans = ans * ((bigmod(p, e+1)+M-1)%M * modInv(p-1) % M) % M;
	}
	return ans;
}

ll POD(vector<PII> &pf){
	int n = pf.size();
	vector<ll> pref(n+2,1), suff(n+2,1);

	for (int i = 1; i <= n; i++){
		pref[i] = (pref[i-1] * (pf[i-1].second+1)) % (M-1);
	}

	for (int i = n; i >= 1; i--){
		suff[i] = (suff[i+1] * (pf[i-1].second+1)) % (M-1);
	}

	ll ans = 1;
	for (int i = 0; i < n; i++){
		auto [p, e] = pf[i];
		ll expo = pref[i] * suff[i+2] % (M-1);
		expo = expo * (1LL*e*(e+1)/2 % (M-1)) % (M-1);
		ans = ans * bigmod(p, expo) % M;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<PII> pf(n);
	for (auto &[p, e]: pf) cin >> p >> e;

	cout << NOD(pf) << " " << SOD(pf) << " " << POD(pf) << "\n";
	return 0;
}