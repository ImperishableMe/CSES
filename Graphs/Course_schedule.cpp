#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
vector<int> g[N];
enum Color {BLACK, GRAY, WHITE};
Color col[N];
int n, m;
vector<int> order;

bool dfs(int u){
    col[u] = GRAY;
    for (auto v : g[u]){
        if (col[v] == GRAY){
            return false;
        }
        if (col[v] == WHITE) {
            if (!dfs(v)) return false;
        }
    }
    col[u] = BLACK;
    order.push_back(u);
    return true;
}

void find_cycle(){
    fill(col, col + n + 1, WHITE);
    for (int i = 1; i <= n; i++){
        if (col[i] == WHITE){
            if (!dfs(i)){
                cout << "IMPOSSIBLE\n"; return;
            }
        }
    }
    reverse(order.begin(), order.end());
    for (auto x : order) cout << x << " ";
    cout << "\n";
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

