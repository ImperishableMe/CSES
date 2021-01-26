#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
int const MOD = 1e9 + 7;

int main(){
    ll n, ans = 0, tmp = 1;
    cin >> n;
    for(int i = 1; i <= n; i++) tmp = (tmp * 2) % MOD;
    cout << tmp << endl;

}