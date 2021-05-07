#include <bits/stdc++.h>
#define ll          long long int
#define uu          first
#define vv          second
#define pii         pair<int,int>
#define pll         pair<ll,ll>
#define tp3         tuple<int,int,int>
#define fastio      ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int INF = 1e9;
const ll MOD = 1e9 + 7;
 
const int N = 1e6 + 6;
 
ll ara[N] , tree[4*N] ;
pll lazy[4*N];
 
void build(int node ,int l ,int r ) {
    if( l == r) {
        tree[node] = ara[l];
        return;
    }
    int mid = (l+r)>>1;
    build( node<<1 , l , mid);
    build(node<<1|1 , mid + 1 , r);
    tree[node] = ( tree[node<<1] + tree[node<<1|1]); //change here
}
 
ll get(pll x, ll nn) {
    ll a = x.uu;
    ll d = x.vv;
    return ( (2*a + (nn-1)*d) * nn) / 2;
}
 
 
void push(int node ,int l ,int r) {
    if( lazy[node].vv) {
        tree[node] += get(lazy[node], r - l + 1);           //change here
        if( l !=r) {
            lazy[node<<1].uu += lazy[node].uu;
            lazy[node<<1].vv += lazy[node].vv;
 
            int mid = (l+r)/2;
            int len = mid - l + 1;
 
            lazy[node<<1|1].uu += lazy[node].uu + lazy[node].vv * len;
            lazy[node<<1|1].vv += lazy[node].vv;
        }
        lazy[node] = {0,0};
    }
}
 
 
void update(int node ,int l, int r, int frm, int to) {
    if( l > r || l > to || r < frm ) return ;
    push(node, l , r);
    if( l >=frm && r <= to) {
        lazy[node].uu += l - frm + 1;
        lazy[node].vv ++;
        push(node, l , r);
        return ;
    }
    int mid = (l+r)>>1;
    update(node<<1 , l , mid , frm , to );
    update(node<<1|1 , mid+1 , r , frm ,to );
    tree[node] = ( tree[node<<1] + tree[node<<1|1] );    //change here
}
 
ll query(int node, int l , int r ,int frm ,int to ) {
    if( l > r || l > to || r < frm ) return 0;    //change here
    push(node, l , r);
    if( l >= frm && r <= to ) return tree[node] ;
    int mid = (l+r)>>1;
    ll q1 = query(node<<1 , l , mid , frm ,to);
    ll q2 = query(node<<1|1 , mid+1 , r , frm , to);
    return (q1 + q2);  //change here
}
 
int main()  {
    fastio;
    int n, q;
    cin>>n>>q;
    for(int i =1 ; i <= n ; i++ ) {
        cin>>ara[i];
    }
    build(1 , 1 , n);
    while( q-- ) {
        int typ ;
        cin>>typ;
        if( typ == 1) {
            int l, r;
            cin>>l>>r;
            update(1 , 1 , n , l , r);
        }
        else {
            int l , r;
            cin>>l>>r;
            cout<<query(1 , 1 , n , l , r)<<'\n';
        }
 
 
        // for(int i =1 ; i <= n ; i++ ) {
        //     cout<<query(1, 1, n, i, i)<<" ";
        // }
        // cout<<'\n';
    }
    return 0;
}
 