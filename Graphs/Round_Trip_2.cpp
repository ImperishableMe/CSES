#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
vector<int> g[N];
enum Color {BLACK, GRAY, WHITE};
bool vis[N];
Color col[N];
int par[N];
int n, m;
int cycle_st = -1, cycle_en = -1;

bool dfs(int u){
    col[u] = GRAY;
    for (auto v : g[u]){
        if (col[v] == GRAY){
            cycle_st = v;
            cycle_en = u;
            return true;
        }
        if (col[v] == WHITE) {
            par[v] = u;
            if (dfs(v)) return true;
        }
    }
    col[u] = BLACK;
    return false;
}

void find_cycle(){
    fill(col, col + n + 1, WHITE);
    for (int i = 1; i <= n; i++){
        if (col[i] == WHITE){
            if (dfs(i)) break;
        }
    }
    if (cycle_st == -1)
        cout << "IMPOSSIBLE\n";
    else {
        vector<int> cycles;
        cycles.push_back(cycle_st);
        for (int cur = cycle_en; cur != cycle_st; cur = par[cur]){
            cycles.push_back(cur);
        }
        cycles.push_back(cycle_st);
        reverse(cycles.begin(), cycles.end());

        cout << cycles.size() << "\n";

        for (auto x : cycles) cout << x << " ";
        cout << "\n";
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }    

    find_cycle();
}

