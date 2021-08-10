#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		int oc = 0;
		for (int i = 0; i < n; i++){
			int tmp; 
			cin >> tmp; 
			oc += tmp & 1;
		}
		cout << (oc?"first":"second") << "\n";
	}
	return 0;
}