#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<bool> dp(n+1,0);
	vector<int> p(k);

	for (auto &x : p) cin >> x;
	dp[0] = 0;
	for (int i = 1; i <= n; i++){
		for (auto x : p){
			if (i >= x && !dp[i-x]) dp[i] = 1;
		}
	}

	for (int i = 1; i <= n; i++){
		cout << (dp[i]?'W':'L');
	}
	cout << endl;

	return 0;
}