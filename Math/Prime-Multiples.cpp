#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

ll const LIM = 3e18;

inline ll f_lcm(ll a, ll b){
	ll g = gcd(a, b);
	a /= g;
	if (1.0 * a * b > LIM) return LIM + 1;
	return a * b;
}

ll n, k;
ll ans;
vector<ll> v;

void recur(int pos, vector<ll> &tmp, ll l){
	if (l > LIM) return;
	if (pos == k) {
		ans += ((tmp.size() & 1)?-1:1) * (n/l);
		return;
	}

	recur(pos+1, tmp, l);

	tmp.push_back(v[pos]);
	ll cur_l = f_lcm(l, v[pos]);

	recur(pos+1, tmp, cur_l);

	tmp.pop_back();
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	v.resize(k);
	for (auto &x : v) cin >> x;
	vector<ll> tmp;
	recur(0, tmp, 1);

	cout << n - ans << "\n";

	return 0;
}