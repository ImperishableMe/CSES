#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
#define all(v) (v).begin(), (v).end()


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, x;
	cin >> n >> x;

	vector<PLL> v(n);
	int cnt = 0;
	for (auto &[x,y] : v) cin >> x, y = cnt++;


	sort(all(v));

	for (int i = 0; i < n; i++){
		ll val = x - v[i].first;
		int r = n-1;
		ll tot = 0;
		for (int l = i+1; l < n; l++){
			while (l < r && v[l].first + v[r].first > val){
				r--;
			}	
			if (l < r && v[l].first + v[r].first == val) {
				cout << v[i].second + 1 << " " << v[l].second + 1 << " " << v[r].second + 1<< endl;
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	
	return 0;
}