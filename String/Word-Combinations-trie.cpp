/**
 * Using trie 
 * */
 
#include <bits/stdc++.h>
using namespace std;
 
 
#define F first
#define S second
using ull = unsigned long long int;
 
typedef long long int ll;
typedef pair < ll,ll > PLL;

const int ALPHA = 26;
const ll M = 1e9 + 7;

struct Node{
	vector<int> ch;
	bool ends = 0;
	Node(){
		ch.assign(ALPHA, -1);
	}
}; 

vector<Node> tr(1);
vector<ll> dp;

void insert(string s){
	reverse(s.begin(), s.end());
	int cur = 0;
	for (auto x: s){
		if (tr[cur].ch[x-'a'] == -1){
			tr[cur].ch[x-'a'] = tr.size();
			tr.push_back(Node());
		}
		cur = tr[cur].ch[x-'a'];
	}
	tr[cur].ends = 1;
}

string s;
ll calc_pref(int pos){
	ll ans = 0;
	Node cur = tr[0];
	for (int i = pos; i > 0; i--){
		int ind = s[i-1] - 'a';
		// cout << "pos " << pos << " " << i << " " << cur.ch[ind] << endl;

		if (cur.ch[ind] == -1) return ans;

		// cout << "again pos " << pos << " " << i << " " << cur.ch[ind] << endl;
		cur = tr[cur.ch[ind]];

		if (cur.ends){
			ans += dp[i-1];
			if (ans >= M) ans -= M;
		}
	}
	return ans;
}
 
void solve(){
	int n;
	cin >> s;
	n = s.size();
	dp.assign(n+2, 0);
	dp[0] = 1;
	int k;
	cin >> k;
	for (int i = 0; i < k; i++){
		string tmp;
		cin >> tmp;
		insert(tmp);
	}

	// cout << tr.size() << endl;

	for (int i = 1; i <= n; i++){
		dp[i] = calc_pref(i);
	}
	cout << dp[n] << "\n";
}
int main(){
 
	ios::sync_with_stdio(false); cin.tie(0);
	int t = 1;
	while (t--) solve();
	
	return 0;
}