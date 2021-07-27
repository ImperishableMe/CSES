#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const M = 1e9 + 7;
int const N = 1e6 + 10;

int cnt[N], mul_cnt[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		int tmp;
		cin >> tmp; 
		cnt[tmp]++;
	}
	for (int i = 1; i < N; i++){
		for (int j = i; j < N; j += i) mul_cnt[i] += cnt[j];
	}
	int g = N - 1;
	while (mul_cnt[g] <= 1) g--;
	cout << g << "\n";
	return 0;
}