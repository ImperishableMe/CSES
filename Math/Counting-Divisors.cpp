#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 1e6 + 10;

int divi[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);

	for (int i = 1; i < N; i++){
		for (int j = i; j < N; j += i){
			divi[j]++;
		}
	}
	int q;
	cin >> q;
	while (q--){
		int n;
		cin >> n;
		cout << divi[n] << "\n";
	}
	return 0;
}