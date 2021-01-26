#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n ;
    if(n == 2 or n == 3){
        cout << "NO SOLUTION\n";
    }
    else {
        for(int i = 1; 2 * i <= n; i++) cout << 2 * i << " ";
        for(int i = 1; 2 * i - 1 <= n; i++) cout << 2*i -1 << " ";
        cout << endl;

    }
}