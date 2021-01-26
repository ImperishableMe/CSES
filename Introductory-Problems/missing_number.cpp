#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    ll n;
    cin >> n;
    ll sum = 0, tmp;
    for(int i = 1; i <= n - 1; i++) cin >> tmp, sum += tmp;
    cout << n * (n+1)/ 2 - sum << endl; 
}