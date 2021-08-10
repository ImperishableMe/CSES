#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		int x = 0;
		for (int i = 0; i < n; i++){
			int tmp; 
			cin >> tmp; x ^= (tmp % 4);
		}
		cout << (x?"first":"second") << "\n";
	}
	return 0;
}