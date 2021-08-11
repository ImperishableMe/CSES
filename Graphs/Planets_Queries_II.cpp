#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
enum Color {WHITE, BLACK, GRAY};

Color col[N];
bool onCycle[N];
int par[N], ans[N], t[N];

void dfs(int u){
	col[u] = GRAY;
	int p = t[u];

	if (col[p] == BLACK){
		ans[u] = 1 + ans[p];
	}
	else if (col[p] == GRAY){
		int csz = 0;
		int cur = u;
		while (true){
			csz++;
			onCycle[cur] = 1;
			if (cur == p) break;
			cur = par[cur];
		}
		cur = u;
		while (true){
			ans[cur] = csz;
			if (cur == p) break;
			cur = par[cur];
		}
	}
	else {
		par[p] = u;
		dfs(p);
	}
	col[u] = BLACK;	

	if (!onCycle[u]){
		ans[u] = 1 + ans[t[u]];
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	fill(col, col+n+1, WHITE);

	for (int i = 1; i <= n; i++) cin >> t[i];

	for (int i = 1; i <= n; i++){
		if (col[i] == WHITE){
			dfs(i);
		}
		else {
			assert(col[t[i]] == BLACK);
		}
	}

	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
	return 0;
}