#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int q;
	cin >> q;
	while (q--){
		int a, b;
		cin >> a >> b;
		int ans = 1, po = a;
		
		while (b){
			if (b&1) ans = (1LL*ans*po) % M;
			po = (1LL*po*po) % M;
			b >>= 1;
		}
		cout << ans << "\n";
	}
	return 0;
}