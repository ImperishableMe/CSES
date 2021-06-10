#include <bits/stdc++.h>
using namespace std;

int const ALPHA = 26;
int const MM = 102;
int aut[MM][ALPHA]; // aut[i][j] means first i character matched(i = 0 means no character matched yet) and 
                    // given char j, where will the state go?

vector<int> prefix_function(string &s){
    vector<int> pi(s.size(), 0); // for i in [0...n-1] pi[i] is the maximum length 
            //of **proper** prefix that is also suffix of the substring s[0..i]

    pi[0] = 0;
    for (int i = 1; i < s.size(); i++){
        int last = pi[i-1];
        while (last > 0 && s[last] != s[i]) last = pi[last-1];
        pi[i] = last + (s[last] == s[i]);
    }
    return pi;
}


void build_automata(string &s){
    vector<int> pi = prefix_function(s);

    for (int i = 0; i < s.size(); i++){
        for (int c = 0; c < ALPHA; c++){
            if (!i) aut[i][c] = s[i] == c + 'A';
            else if (s[i] == c + 'A') aut[i][c] = i+1;
            else aut[i][c] = aut[pi[i-1]][c];
        }
    }

    for (int c = 0; c < ALPHA; c++){
        aut[s.size()][c] = s.size();  // creating the edges when entire string is matched
                                      // here we are adding self-loop as the problem required,
                                      // may need to change according to problem.            
    }
}
const int M = 1e9 + 7;

int dp[1010][101];
int n;
string s;

int DP(int l, int state){
    if (l == n) return state == s.size();
    int &ret = dp[l][state];
    if (ret != -1) return ret;
    ret = 0;
    for (int c = 0; c < ALPHA; c++){
        int nxt = aut[state][c];
        ret += DP(l+1, nxt);
        if (ret >= M) ret -= M;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    cin >> s;
    build_automata(s);
    // memset(dp, -1, sizeof dp);
    dp[0][0] = 1;
    for (int l = 0; l < n; l++){
        for (int st = 0; st <= s.size(); st++){
            for (int c = 0; c < ALPHA; c++){
                dp[l+1][aut[st][c]] += dp[l][st];
                if (dp[l+1][aut[st][c]] >= M) 
                    dp[l+1][aut[st][c]] -= M;
            }
        }
    }
    cout << dp[n][s.size()] << "\n";
    // cout << DP(0,0) << "\n";
    return 0; 
}