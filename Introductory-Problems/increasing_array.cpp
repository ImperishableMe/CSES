#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    ll n, ans = 0;
    cin >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 1; i < n; i++){
        ans += max(0LL, v[i - 1] - v[i]);
        v[i] = max(v[i], v[i-1]);
    }
    cout << ans << endl;
    return 0;  

}