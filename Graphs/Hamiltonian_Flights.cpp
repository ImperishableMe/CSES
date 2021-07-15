#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
int const M = 1e9 + 7;
int const N = 21;

inline void addMod(int &x, int y) {
	x += y;
	if (x >= M) x -= M;
}
int dp[N][1<<N];
int n, m;
vector<int> g[N];

// int DP(int pos, int msk){
// 	if (pos == n - 1) return msk == ((1<<n)-1);
// 	if (msk == (1<<n)-1) return 0;
// 	int &ret = dp[pos][msk];
// 	if (ret != -1) return ret;
// 	ret = 0;
// 	for (auto x : g[pos]){
// 		if (msk & (1<<x)) continue;
// 		addMod(ret, DP(x, msk ^ (1<<x)));
// 	}
// 	return ret;
// }

int main(){
	ios::sync_with_stdio(0);
	memset(dp, 0, sizeof dp);
	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
	}

	dp[0][1] = 1;

	for (int msk = 0; msk < (1<<n); msk++){
		if ((msk & 1) == 0) continue;
		for (int i = 0; i < n; i++){
			if (!(msk & (1<<i))) continue;
			// if (!(msk & (1<<(n-1)))) continue;
			for (auto x : g[i]){
				if (msk & (1<<x)) continue;
				addMod(dp[x][msk^(1<<x)], dp[i][msk]);
			}
		}
	}
	cout << dp[n-1][(1<<n)-1] << "\n";

	return 0;
}