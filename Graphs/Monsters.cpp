#include <bits/stdc++.h>
using namespace std;

using PII = pair<int,int>;

int const N = 1'010;
int n, m;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,-1,1};
char mv[] = "DULR";
vector<string>g;
bool vis[N][N];
int dist[N][N];

bool isAllowed(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m && g[x][y] != '#' && !vis[x][y];
}

void multiSourceBFS(){
    memset(dist, 0x3f, sizeof dist);
    queue <PII> q;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (g[i][j] == 'M'){
                dist[i][j] = 0;
                vis[i][j] = 1;
                q.push({i,j});
            }
        }
    }
    while (!q.empty()){
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isAllowed(nx, ny)){
                vis[nx][ny] = 1;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    // cout << "output" << endl;
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < m; j++){
    //         cout << dist[i][j] << " \n"[j+1==m];
    //     }
    // }
}

bool foundBorder(int x, int y){
    return (x == 0 || x + 1 == n || y == 0 || y + 1 == m);
}

void bfs(int ax, int ay){
    vector<vector<int>> last(n, vector<int>(m,-1)), step(n, vector<int> (m, 0));
    queue<PII> q;
    q.push({ax, ay});
    step[ax][ay] = 0;
    vis[ax][ay] = 1;

    while (!q.empty()){
        auto [x, y] = q.front(); 
        q.pop();

        if (foundBorder(x,y)){
            cout << "YES\n";
            vector<int> mvs;
            PII cur = {x, y};
            while (cur != PII(ax, ay)) {
                mvs.push_back(last[cur.first][cur.second]);
                int l = last[cur.first][cur.second];
                cur.first += dx[l] * -1;
                cur.second += dy[l] * -1;
            }
            reverse(mvs.begin(), mvs.end());
            cout << mvs.size() << "\n";
            for (auto x : mvs) cout << mv[x];
            cout << "\n";
            exit(0);
        }

        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isAllowed(nx, ny) && dist[nx][ny] > 1 + step[x][y]){
                vis[nx][ny] = 1;
                q.push({nx, ny});
                last[nx][ny] = i;
                step[nx][ny] = step[x][y] + 1;
            }
        }
    }

    cout << "NO\n";

}


int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    g.resize(n);

    for (int i = 0; i < n; i++){
        cin >> g[i];
    }
    multiSourceBFS();
    memset(vis, 0, sizeof vis);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (g[i][j] == 'A') {
                bfs(i,j);
            }
        }
    }

    return 0;
}