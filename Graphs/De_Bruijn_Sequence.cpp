#include <bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
map<string, bool> seen;
int n, m;
string edges;

void dfs(string u){
	string tmp;
	for (int i = 0; i <= 1; i++){
		tmp = u + char('0' + i);
		if (!seen.count(tmp)) {
			seen[tmp] = 1;
			dfs(tmp.substr(1));
			edges += '0' + i;
		}
	}
}

int main(){

	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;

	string st = string(n-1, '0');
	// cout << st << endl;

	dfs(st);

	reverse(edges.begin(), edges.end());
	// cout << st + edges << "\n";
	// cout << edges << endl;
	st += edges;
	cout << st << "\n";

	return 0;
}