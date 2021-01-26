#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin >> n;
    vector<long long>val;
    while(true){
        val.push_back(n);
        if(n == 1) break;
        if(n & 1)  n = 3 * n + 1;
        else    n /= 2;
    }
    for(auto x : val) cout << x << " ";
    cout << endl;
    return 0;

}