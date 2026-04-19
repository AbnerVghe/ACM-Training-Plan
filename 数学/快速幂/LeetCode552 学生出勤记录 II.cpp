#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int MOD = 1e9 + 7;

struct s{
    ll a[105][105],r,c;
    s(int _r=0,int _c=0){
        r=_r,c=_c;memset(a,0,sizeof a);
        if(c==0)c=r;
    }
    void unit(){
        memset(a,0,sizeof a);
        for(int i=1;i<=r;i++)a[i][i]=1;
    }
    void set(const vector<vector<int>>& v){
        foreach(1, r, i){
            foreach(1, c, j){
                a[i][j] = v[i-1][j-1];
            }
        }
    }
    s operator*(const s t)const{
        s ans(r,t.c);int n=r,m=t.c;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                for(int k=1;k<=c;k++)ans.a[i][j]=(ans.a[i][j]+a[i][k]*t.a[k][j]%MOD)%MOD;return ans;
    }
    /* s operator+(const s t)const{
        s ans(r,c);
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)ans.a[i][j]=a[i][j]+t.a[i][j];
        return ans;
    } */
    void print() {
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++) cout<<a[i][j]<<" ";
            cout << endl;
        }
    }
    s pow(ll b) {
        s ans(r,c),a=*this;ans.unit();
        while(b){if(b&1)ans=ans*a;a=a*a;b>>=1;}
        return ans;
    }
    s operator%(const ll t)const{
        s ans=*this;
        for(int i=1;i<=r;i++)
            for (int j=1;j<=c;j++)ans.a[i][j]%=t;return ans;
    }
    s pow(ll b,ll p){
        s ans(r,c),a=*this;ans.unit();
        while(b){if(b&1)ans=ans*a%p;a=a*a%p;b>>=1;}
        return ans%p;
    }
}; 

class Solution {
public:
    int checkRecord(int n) {
        if(n == 1) return 3;
        
        s start(1, 6);
        start.set({{1, 1, 0, 1, 0, 0}});
        s mtx(6, 6);
        mtx.set({
            {1, 1, 0, 1, 0, 0},
            {1, 0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 1},
            {0, 0, 0, 1, 0, 0}
        });
        s res(1, 6);
        res = start * mtx.pow(n-1, MOD);
        ll ans = 0;
        foreach(1, 6, i) ans = (ans + res.a[1][i])%MOD;
        return ans;
    }
};