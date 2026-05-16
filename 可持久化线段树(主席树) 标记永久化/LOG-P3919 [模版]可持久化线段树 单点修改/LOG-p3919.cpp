#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e6+7;
const int T = N * 23;

int arr[N];
int root[N], Left[T], Right[T], val[T], cnt;//val只有叶节点才有

int build(int l, int r){//返回头结点编号
    int rt = ++cnt;
    if(l == r){
        val[rt] = arr[l];
    }
    else{
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
    }
    return rt;
}

int update(int x, int v, int l, int r, int p){
    int rt = ++cnt;
    //克隆原本节点信息
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    val[rt] = val[p];
    if(l == r){
        val[rt] = v;
    }
    else{
        int mid = (l + r) >> 1;
        if(x <= mid) Left[rt] = update(x, v, l, mid, Left[rt]);
        else Right[rt] = update(x, v, mid+1, r, Right[rt]);
    }
    return rt;
}

int query(int x, int l, int r, int p){
    if(l == r){
        return val[p];
    }
    int mid = (l + r) >> 1;
    if(x <= mid) return query(x, l, mid, Left[p]);
    else return query(x, mid+1, r, Right[p]);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> arr[i];
    }
    root[0] = build(1, n);
    foreach(1, m, j){
        int version, opt, p;
        cin >> version >> opt >> p;
        if(opt == 1){
            int v;
            cin >> v;
            root[j] = update(p, v, 1, n, root[version]);
        }
        else{
            root[j] = root[version];
            cout << query(p, 1, n, root[j]) << '\n';
        }
    }
}