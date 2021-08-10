#include <bits/stdc++.h>
using namespace std;

int const N = 110;
int n, k;

double bigExpo(double a, int k){
	double p = a, ret = 1;
	while (k){
		if (k & 1) ret *= p;
		p *= p;
		k >>= 1;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	double ans = 0;
	for (int i = 1; i <= k; i++){
		double pi = bigExpo(1.0*i/k, n) - bigExpo(1.0*(i-1)/k, n);
		ans += i * pi;
	}

	cout << setprecision(6) << fixed << ans << "\n";
	// cout << bigExpo(2, 3) << "\n";
}