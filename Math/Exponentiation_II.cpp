#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;

int bigmod(int a, int b, int mod = M){
	int ans = 1, po = a;
	while (b){
		if (b&1) ans = (1LL*ans*po) % mod;
		po = (1LL*po*po) % mod;
		b >>= 1;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int q;
	cin >> q;
	while (q--){
		int a, b, c;
		cin >> a >> b >> c;
		int exp = bigmod(b, c, M - 1);
		cout << bigmod(a, exp) << "\n";
	}
	return 0;
}