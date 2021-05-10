#include <bits/stdc++.h>
using namespace std;

int const N = 1005;

int t[N][N];
string g[N];

void update(int x, int y, int val){
    // cout << "U " << x << " " << y << endl;

    for ( ; x < N; x += (x & (-x))){
        for (int _y = y; _y < N; _y += (_y & (-_y))){
            t[x][_y] += val;
        }
    }
}

int Q(int x, int y){
    int ans = 0;
    // cout << "Q " << x << " " << y << endl;
    for ( ; x > 0; x -= (x & (-x))){
        for (int _y = y; _y > 0; _y -= (_y & (-_y))){
            ans += t[x][_y];
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n , q;
    cin >> n >> q;

    for (int i = 0; i < n; i++){
        cin >> g[i];

        for (int j = 1; j <= n; j++){
            if (g[i][j-1] == '*') update(i+1, j, 1);
        }
    }

    while (q--){
        int t; ///, x, y;
        cin >> t;// >> x >> y;
        if (t == 1){
            int x, y;
            cin >> x >> y;
            if (g[x-1][y-1] == '*') update(x, y, -1);
            else update(x, y, 1);
            g[x-1][y-1] = ((g[x-1][y-1] != '*')? '*': '.');

        }
        else {
            int x1, y1, x, y;
            cin >> x >> y >> x1 >> y1;

            // cout << "Q  <<" << x1 << " "<< y1 << " " << Q(x1, y1) << endl;

            int ans = Q(x1, y1) - Q(x1, y-1) - Q(x-1, y1) + Q(x-1, y-1);
            cout << ans << endl;
        }
    }

    return 0;
}