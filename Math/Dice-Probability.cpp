#include <bits/stdc++.h>
using namespace std;

int const N = 110;
int n, k;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, a, b;
	cin >> n >> a >> b;
	
	vector<vector<double>> dp(n+2, vector<double>(6*n+2, 0));
	dp[0][0] = 1;

	for (int thr = 1; thr <= n; thr++){
		for (int s = 0; s <= 6*n; s++){
			for (int l = 1; l <= 6; l++){
				if(s >= l)dp[thr][s] += 1.0/6 * dp[thr-1][s-l];
			}
		}
	}
	double ans = 0;
	for (int i = a; i <= b; i++) ans += dp[n][i];
	cout << setprecision(6) << fixed << ans << endl;

}