#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 7e5+7;
int tree[N][12], pass[N];
int cnt;

void build(){
    cnt = 1;
}

int to_path(char c){
    if(c == '#') return 10;
    if(c == '-') return 11;
    else return c - '0';
}

void ins(string s){
    int cur = 1;
    pass[cur]++;
    for(auto c: s){
        int path = to_path(c);
        if(!tree[cur][path]) tree[cur][path] = ++cnt;
        cur = tree[cur][path];
        pass[cur]++;
    }
}

int src(string s){
    int cur = 1;
    for(auto c: s){
        int path = to_path(c);
        if(!tree[cur][path]) return 0;
        cur = tree[cur][path];
    }
    return pass[cur];
}

void clr(){
    foreach(1, cnt, i){
        foreach(0, 11, j) tree[i][j] = 0;
        pass[i] = 0;
    }
}

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param b int整型vector<vector<>> 
     * @param a int整型vector<vector<>> 
     * @return int整型vector
     */
    vector<int> countConsistentKeys(vector<vector<int> >& b, vector<vector<int> >& a) {
        // write code here
        build();
        for(auto key: a){
            string s = "";
            foreach(0, key.size()-2, i){
                string c = to_string(key[i+1] - key[i]);
                s += c;
                s += '#';
            }
            //cout << s << ' ';
            ins(s);
        }
        //cout << '\n';
        vector<int> ans;
        for(auto key: b){
            string s = "";
            foreach(0, key.size()-2, i){
                string c = to_string(key[i+1] - key[i]);
                s += c;
                s += '#';
            }
            //cout << s << ' ';
            ans.push_back(src(s));
        }
        clr();

        return ans;
    }
};