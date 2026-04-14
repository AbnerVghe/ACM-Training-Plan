#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1e5+7;
vector<int> p[N];
string str;

struct Info{
    int maxRoot, maxNRoot;  
};

Info dfs(int x){
    if(!p[x].size()) return (Info){1, 1};

    int max1 = 0, max2 = 0;
    int maxNRoot = 1;
    for(auto v: p[x]){
        Info infov = dfs(v);
        maxNRoot = max(maxNRoot, infov.maxNRoot);
        if(str[x] != str[v]){
            if(infov.maxRoot > max1){
                max2 = max1;
                max1 = infov.maxRoot;
            }
            else if(infov.maxRoot > max2){
                max2 = infov.maxRoot;
            }
        }
    }
    int maxRoot = max1 + 1;
    maxNRoot = max(maxNRoot, max1+max2+1);
    return (Info){maxRoot, maxNRoot};
}

class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        foreach(0, n-1, i) p[i].clear();

        str = s;
        foreach(0, n-1, i){
            int fa = parent[i];
            if(fa != -1) p[fa].push_back(i);
        }

        return dfs(0).maxNRoot;
    }
};