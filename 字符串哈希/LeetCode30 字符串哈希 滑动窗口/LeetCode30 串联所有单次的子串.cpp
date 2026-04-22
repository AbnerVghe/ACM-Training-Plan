#include<bits/stdc++.h>
#define ll unsigned long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e4+7, base = 499;
ll power[N], hashVal[N];
int n, m;

ll hs(string s){
    ll ans = 0;
    for(auto c: s){
        ans = ans*base + c-'a'+1;
    }
    return ans;
}

void build(string s){
    power[0] = 1;
    foreach(1, n, i) power[i] = power[i-1] * base;

    hashVal[0] = s[0] - 'a' + 1;
    foreach(1, n-1, i) hashVal[i] = hashVal[i-1]*base + s[i]-'a'+1;
}

ll cal_hs(int l, int r){
    ll ans = hashVal[r-1];
    if(l){
        ans -= hashVal[l-1] * power[r-l];
    }
    return ans;
}

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        n = s.length();
        m = words[0].length();
        vector<int> ans;
        build(s);
        unordered_map<ll, int> arr;
        for(auto word: words){
            ll index = hs(word);
            arr[index]++;
        }
        for(int start = 0; start < m && start+m*words.size() <= n; start++){
            int debt = words.size();
            unordered_map<ll, int> window;
            for(int l = start, r = start+m, part = 0; part < words.size(); l += m, r += m, part++){
               ll cur = cal_hs(l, r);
               window[cur]++;
               if(window[cur] <= arr[cur]) debt--;
            }
            if(!debt) ans.push_back(start);
            for(int l1 = start, r1 = start+m, l2 = start+m*words.size(), r2=start+m*words.size()+m; r2 <= n; l1 += m, l2 += m, r1 += m, r2 += m){
                ll pre = cal_hs(l1, r1), now = cal_hs(l2, r2);
                window[pre]--;
                if(window[pre] < arr[pre]) debt++;
                window[now]++;
                if(window[now] <= arr[now]) debt--;
                if(!debt) ans.push_back(r1);
            }
        }

        return ans;
    }
};