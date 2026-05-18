#include<bits/stdc++.h>
#define int long long
#define double long double
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const double eqs = 1e-6;
const int N = 1010;
double dis[N];
int cnt[N];
bool enter[N];
int n, t;
int s, s1, s2;
vector<pair<int, double>> p[N];
queue<int> Q;

struct Vow{
    int A, B;
    double k;
}vow[2][N];
pair<int, double> score[N];

void prepare(){
    while(Q.size()) Q.pop();
    foreach(0, n+1, i){
        dis[i] = INF;
        p[i].clear();
        cnt[i] = enter[i] = 0;
    }
}

bool spfa(int yd){
    dis[yd] = 0;
    enter[yd] = 1;
    Q.push(yd);
    while(Q.size()){
        int u = Q.front();
        enter[u] = 0;
        Q.pop();
        for(auto e: p[u]){
            int v = e.first;
            double w = e.second;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                if(enter[v]) continue;
                enter[v] = 1;
                Q.push(v);
                cnt[v]++;
                if(cnt[v] > n+1) return 1;//有人女装
            }
        }
    }
    return 0;//没人女装
}

bool check(double T){
    prepare();
    foreach(1, n, i){
        p[0].push_back({i, 0});
    }
    foreach(1, s1, i){
        int A = vow[0][i].A, B = vow[0][i].B;
        double k = vow[0][i].k;
        if(k-T > 0) p[A].push_back({B, -log(k-T)});
    }
    foreach(1, s2, i){
        int A = vow[1][i].A, B = vow[1][i].B;
        double k = vow[1][i].k;
        p[A].push_back({B, log(k+T-eqs)});
    }
    foreach(1, t, i){
        int C = score[i].first;
        double x = score[i].second;
        p[n+1].push_back({C, log(x)});
        p[C].push_back({n+1, -log(x)});
    }
    return spfa(0);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> s >> t;
    foreach(1, s, i){
        int opt, A, B;
        double k;
        cin >> opt >> A >> B >> k;
        if(opt == 1){
            vow[0][++s1] = {A, B, k};
        }
        else vow[1][++s2] = {A, B, k};
    }
    foreach(1, t, i){
        int C;
        double x;
        cin >> C >> x;
        score[i] = {C, x};
    }
    double L = 0, R = 10, T = 0;
    while(R-L >= eqs){
        double mid = (L + R) / 2;
        if(check(mid)){
            T = mid;
            L = mid + eqs;
        }
        else R = mid - eqs;
    }
    if(T == 0){
        cout << -1;
    }
    else cout << T;
}