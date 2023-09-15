#include <vector>
#include <iostream>
#include <array>
#include <numeric>

using namespace std;

#define MAXN 201
#define MAXK 100
#define INF numeric_limits<int>::max()



// void PrintDP(int n, int k){
//     // 임시출력
//     for(int p = 1; p <= n; ++p){
//         for(int t = 0; t < k; ++t){
//             if(dp[t][p] == INF)
//                 cout << "F ";
//             else
//                 cout << dp[t][p] << " ";
//         }
//         cout << "\n";
//     }
//     cout << "\n";
// }

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    array<array<int, MAXN>, MAXK> dp;   // dp[t][p] = t번째의 위치가 p일때 오류수정의 최소횟수
    array<vector<int>, MAXN> edges;
    
    // dp 초기화
    for(int p = 1; p <= n; ++p){
        dp[0][p] = INF;
    }
    dp[0][gps_log[0]] = 0;
    
    // 경로를 편하게 변경
    for(vector<int>& edge : edge_list){
        int u = edge[0];
        int v = edge[1];
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for(int p = 1; p <= n; ++p){
        edges[p].push_back(p);
    }
    
    // dp 계산
    for(int t = 1; t < k; ++t){
        for(int p = 1; p <= n; ++p){
            dp[t][p] = INF;
            for(int prevP : edges[p]){
                if(dp[t - 1][prevP] == INF)
                    continue;
                
                int nModify = dp[t - 1][prevP] + (gps_log[t] == p ? 0 : 1);
                dp[t][p] = min(dp[t][p], nModify);
            }
        }
        
        // 임시출력
        //PrintDP(n, k);
    }
    
    int ans = dp[k - 1][gps_log[k - 1]];
    if(ans == INF)
        return -1;
    else
        return ans;
}