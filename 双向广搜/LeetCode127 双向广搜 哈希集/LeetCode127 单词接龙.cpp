#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> book(wordList.begin(), wordList.end());
        if(!book.count(endWord)) return 0;

        unordered_set<string> smallset, bigset, nextset;
        smallset.insert(beginWord);
        bigset.insert(endWord);
        for(int len = 2; smallset.size(); len++){
            for(const auto& str: smallset){
                string newstr = str;
                foreach(0, str.length()-1, i){
                    char old = str[i];
                    for(char c = 'a'; c <= 'z'; c++){
                        if(old == c) continue;
                        newstr[i] = c;
                        if(bigset.count(newstr)) return len;
                        if(book.count(newstr)){
                            nextset.insert(newstr);
                            book.erase(newstr);
                        }
                    }
                    newstr[i] = old;
                }
            }
            if(nextset.size()>bigset.size()){
                unordered_set<string> tmp = bigset;
                bigset = nextset;
                smallset = tmp;
            }
            else{
                smallset = nextset;
            }
            nextset.clear();
        }
        return 0;
    }
};

signed main(){
    Solution slu;
    vector<string> vec = {"hot","dot","dog","lot","log","cog"};
    cout << slu.ladderLength("hit", "cog", vec);
}