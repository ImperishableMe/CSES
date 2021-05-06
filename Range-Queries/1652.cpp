#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
    vector<string> g(n);

    for (int i = 0; i < n; i++) cin >> g[i];

    // for (int i = 0; i < n; i++) cout << g[i] << endl;


    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            // cout << i << " " << j << endl;
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + (g[i-1][j-1] == '*');
        }
    }

    // cout << "hello" << endl;

    while (q--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        // cout << "DBG " << dp[x1][y1] << endl;
        // cout << "DBG " << dp[x2][y2] << endl;
        // cout << "DBG " << dp[x1-1][y1] << endl;
        // cout << "DBG " << dp[x1][y1-1] << endl;
        cout << dp[x2][y2] - dp[x2][y1-1] 
        - dp[x1-1][y2] + dp[x1-1][y1-1] << "\n";
    }
    return 0;
}