#include <bits/stdc++.h>
using namespace std;

int const N = 1010;
using PII = pair<int,int>;

bool vis[N][N];
vector<string> g;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
string mv = "LRUD";
int par[N][N];
int n, m;

PII a, b;

bool isValid(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#';
}


void bfs(PII src){

	queue<PII> q;
	q.push(src);
	vis[src.first][src.second] = 1;

	while (q.size()){
		auto [x, y] = q.front();
		q.pop();

		for (int i = 0; i < 4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (isValid(nx, ny) && !vis[nx][ny]){
				vis[nx][ny] = 1;
				par[nx][ny] = i;
				q.push({nx, ny});
			}
		}
	}
}


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < n; i++) cin >> g[i];

	memset(par, -1, sizeof par);

	int ans = 0;
	for (int x = 0; x < n; x++){
		for (int y = 0; y < m; y++){
			if (g[x][y] == 'A'){
				a = {x, y};
			}
			if (g[x][y] == 'B'){
				b = {x, y};
			}
		}
	}
	bfs(a);

	if (!vis[b.first][b.second]) {
		cout << "NO\n"; return 0;
	}

	cout << "YES\n";
	vector<int> mvs;
	int cx = b.first, cy = b.second;

	while (par[cx][cy] != -1){
		int m = par[cx][cy];
		cx += dx[m] * -1;
		cy += dy[m] * -1;
		mvs.push_back(m);
	}

	cout << mvs.size() << "\n";

	reverse(mvs.begin(), mvs.end());

	for (auto m : mvs) cout << mv[m];
	cout << "\n";

	return 0;
}