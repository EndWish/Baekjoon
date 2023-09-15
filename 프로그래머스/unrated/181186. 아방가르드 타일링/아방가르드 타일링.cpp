#include <string>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

#define MAXN 100'001

array<long long, MAXN> dp;
array<long long, MAXN> sums;

int solution(int n) {
    // dp[i] = dp[i - 3] * 5 + dp[i - 2] * 2 + dp[i - 1]
    
    dp[0] = 1; sums[0] = 1;
    dp[1] = 1; sums[1] = 1;
    dp[2] = 3; sums[2] = 3;
    for(int i = 3; i <= n; ++i){
        dp[i] = dp[i - 3] * 5 + dp[i - 2] * 2 + dp[i - 1];
        if(4 <= i)
            dp[i] += sums[i - 4] * 2;
        if(5 <= i)
            dp[i] += sums[i - 5] * 2;
        if(6 <= i)
            dp[i] += sums[i - 6] * 4;
        
        dp[i] %= 1'000'000'007LL;
        sums[i] = (sums[i - 3] + dp[i]) % 1'000'000'007LL;
        //cout << "dp[ " << i << "] : " << dp[i] << "\n";
    }
    
    return dp[n];
}