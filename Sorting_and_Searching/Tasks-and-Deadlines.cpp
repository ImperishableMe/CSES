#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<PLL> jobs(n);
	for (auto &[dur, ded] : jobs) cin >> dur >> ded;

	ll ans = 0;
	sort(jobs.begin(), jobs.end());
	ll cur_time = 0;
	for (auto [a,b]: jobs){
		cur_time += a;
		ans += b - cur_time;
	}
	cout << ans << '\n';
	
	return 0;
}