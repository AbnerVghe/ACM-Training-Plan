 #include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e4+7;

int dfn[N], low[N];
int sccCnt, stk[N], top, sccSz[N];
int belong[N], cntD;
int oD[N], rD[N];

vector<int> p[N];

void tarjan(int x){
	low[x] = dfn[x] = ++cntD;
	stk[++top] = x;

	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
		}
		else if(!belong[v]){
			low[x] = min(low[x], dfn[v]);
		}
	}

	if(low[x] == dfn[x]){
		sccCnt++;
		int pop;
		do{
			pop = stk[top--];
			belong[pop] = sccCnt;
			sccSz[sccCnt]++;
		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n;
	cin >> n;
	foreach(1, n, i){
		int x;
        do{
            cin >> x;
            if(x) p[i].push_back(x);
        }while(x);
	}
	foreach(1, n, i){
		if(!dfn[i]) tarjan(i);
	}
	foreach(1, n, i){
		int scc1 = belong[i];
		for(auto v: p[i]){
			int scc2 = belong[v];
			if(scc1 == scc2) continue;

            oD[scc1]++;
			rD[scc2]++;
		}
	}
	int ansO = 0, ansR = 0;
    foreach(1, sccCnt, i){
        if(!oD[i]) ansO++;
        if(!rD[i]) ansR++;
    }
    if(sccCnt == 1) cout << 1 << '\n' << 0;
	else cout << ansR << '\n' << max(ansO, ansR);
}