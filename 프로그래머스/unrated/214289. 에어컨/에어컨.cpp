#include<iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

int dp[51][1000];

int& DP(int temperature, int time);
bool IsValid(int temperature, int time);

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    fill_n(&dp[0][0], 51 * 1000, INF);
    DP(temperature, 0) = 0;
    
    for (int time = 0; time < onboard.size() - 1; ++time) {
        for (int temp = -10; temp <= 40; ++temp) {
            // 불가능한 경우 제외
            if (DP(temp, time) == INF)
                continue;
            if (onboard[time] == 1 && (temp < t1 || t2 < temp))
                continue;

            // 에어컨을 켜지 않는 경우
            if (temp < temperature) {
                DP(temp + 1, time + 1) = min(DP(temp, time), DP(temp + 1, time + 1));
            }
            else if (temp > temperature) {
                DP(temp - 1, time + 1) = min(DP(temp, time), DP(temp - 1, time + 1));
            }
            else {
                DP(temp, time + 1) = min(DP(temp, time), DP(temp, time + 1));
            }

            // 에어컨을 켜서 온도가 올라가는 경우
            if(temp < 40)
                DP(temp + 1, time + 1) = min(DP(temp, time) + a, DP(temp + 1, time + 1));

            // 에어컨을 켜서 온도가 내려가는 경우
            if(-10 < temp)
                DP(temp - 1, time + 1) = min(DP(temp, time) + a, DP(temp - 1, time + 1));
            
            // 에어컨을 켜서 온도가 유지하는 경우
            DP(temp, time + 1) = min(DP(temp, time) + b, DP(temp, time + 1));
        }
    }

    int ans = INF;
    if (onboard[onboard.size() - 1] == 0) {
        for (int temp = -10; temp <= 40; ++temp) {
            ans = min(ans, DP(temp, onboard.size() - 1));
        }
    }
    else {
        for (int temp = t1; temp <= t2; ++temp) {
            ans = min(ans, DP(temp, onboard.size() - 1));
        }
    }
    
    return ans;
}

bool IsValid(int temperature, int time) {
    if (-10 <= temperature && temperature <= 40)
        return true;
    return false;
}

int& DP(int temperature, int time) {
    return dp[temperature + 10][time];
}