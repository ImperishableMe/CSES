#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 1e6 + 10;

ll cnt[N], multi[N];

inline ll nc2(ll n){
	return n * (n-1)/2;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n;
	cin >> n;
	
	vector<int> v(n);
	for (auto &x : v) cin >> x, cnt[x]++;

	for (int i = 1; i < N; i++){
		for (int j = i; j < N; j += i) multi[i] += cnt[j];
		multi[i] = nc2(multi[i]);
	}	

	for (int i = N - 1; i >= 1; i--){
		for (int j = i*2; j < N; j += i){
			multi[i] -= multi[j];
		}
	}
	cout << multi[1] << "\n";
	return 0;
}