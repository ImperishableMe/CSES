#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
int const LOG = 31;
int sp[LOG][N];


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, q;
	cin >> n >> q;
	memset(sp, -1, sizeof sp);

	for (int i = 1; i <= n; i++) cin >> sp[0][i];

	for (int lg = 1; lg < LOG; lg++){
		for (int i = 1; i <= n; i++){
			sp[lg][i] = sp[lg-1][sp[lg-1][i]];
		} 
	}


	while (q--){
		int x, k;
		cin >> x >> k;
		// cout << "answering " <<  x << " " << k << endl;
		int cur = x;
		for (int lg = LOG - 1; lg >= 0; lg--){
			// cout << lg << "  " << cur << endl;
			if ((k & (1<<lg))) {
				cur = sp[lg][cur];
			}
		}
		cout << cur << "\n";
	}
	return 0;
}