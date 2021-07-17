#include <bits/stdc++.h>
using namespace std;

int const N = 1010;

bool vis[N][N];
vector<string> g;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
int n, m;

bool isValid(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#';
}


void dfs(int x, int y){
	if (vis[x][y]) return;
	vis[x][y] = 1;

	for (int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isValid(nx, ny))
			dfs(nx, ny);
	}
}


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < n; i++) cin >> g[i];

	int ans = 0;
	for (int x = 0; x < n; x++){
		for (int y = 0; y < m; y++){
			if (g[x][y] == '.' && !vis[x][y]){
				dfs(x, y);
				ans++;
			}
		}
	}
	cout << ans << "\n";
	return 0;
}