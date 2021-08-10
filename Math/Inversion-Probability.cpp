#include <bits/stdc++.h>
using namespace std;


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;

	vector<int> r(n);
	for (auto &x: r) cin >> x;

	double ans = 0;
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			double cur = 0;
			for (int vi = 1; vi <= r[i]; vi++){
				cur += (1.0 / r[i] / r[j]) * min(vi-1, r[j]);
			}
			ans += cur;
		}
	}
	cout << setprecision(6) << fixed << ans << "\n";
	return 0;
}