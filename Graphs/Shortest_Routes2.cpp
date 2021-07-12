#include <bits/stdc++.h>
using namespace std;
int const N = 5'50;
using ll = long long int;
using PLL = pair<ll,ll>;
ll const INF = 1e18;

ll dist[N][N]; // dist a -> b, dist[a][b]
int main(){
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1;i <= n; i++)
        for (int j = 1; j <= n; j++) 
            dist[i][j] = (i==j)? 0LL : INF;

    for (int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = min(c * 1LL, dist[a][b]);
    } 


    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                dist[i][j] = min(dist[i][j], 
                    dist[i][k] + dist[k][j]);
                
            }
        }
    }

    while(q--){
        int a, b;
        cin >> a >> b;
        if (dist[a][b] >= INF) cout << "-1\n";
        else cout << dist[a][b] << "\n";
    }
}