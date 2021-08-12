#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
#define all(v) (v).begin(), (v).end()


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;

	vector<int> v(n+1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];

	stack<int> st;
	st.push(0);
	for (int i = 1; i <= n; i++){
		assert(st.size());
		while (v[st.top()] >= v[i]) st.pop();
		cout << st.top() << " ";
		st.push(i);
	}
	cout << endl;
	return 0;
}