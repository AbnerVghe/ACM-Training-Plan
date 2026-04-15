#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(!n) return 1;
		int ans = 10;
		for(int s = 9, i = 9, k = 2; k <= n; k++, i--){
			s *= i;
			ans += s;
		}
		return ans;
    }
};