#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5e3+7;
int h[N];

priority_queue<pii> Q;

struct Building{
    int L, H, R;
}a[N];

bool cmp(Building A, Building B){
    return A.L < B.L;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int L, H, R;
    int n = 0;
    int maxR = 0;
    while(cin >> L >> H >> R){
        a[++n] = {L, H, R};
        maxR = max(maxR, R);
    }
    maxR++;
    sort(a+1, a+n+1, cmp);
    int j = 1;
    foreach(1, maxR, i){
        while(j <= n && a[j].L <= i){
            Q.push({a[j].H, a[j].R});
            j++;
        }
        while(Q.size()){
            auto U = Q.top();
            int H = U.first, R = U.second;
            if(R <= i){
                //cout << "Pop " << H << ' ' << R << " when i = " << i << '\n';
                Q.pop();
                continue;
            }
            h[i] = H;
            break;
        }
    }
    /* foreach(1, maxR, i) cout << left << setw(4) << i << ' ';
    cout << '\n';
    foreach(1, maxR, i) cout << left << setw(4) << h[i] << ' '; */
    int now = 0;
    foreach(1, maxR, i){
        if(now != h[i]){
            cout << i << ' ' << h[i] << ' ';
        }
        now = h[i];
    }
}