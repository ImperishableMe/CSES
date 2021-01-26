#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin >> s;
    int ans = 0, l = 0;
    for(int i = 0; i < s.size(); ){
        int cur = i;
        while(i < s.size() and s[i] == s[cur]) i++,l++;
        ans = max(ans, l);
        l = 0;
    }
    cout << ans << endl;
}