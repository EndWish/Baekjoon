#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <numeric>

using namespace std;

#define MAXN 100'001
#define INF numeric_limits<int>::max()

array<pair<int,int>, 10> poses =   { pair<int,int>(3,1),
                                    pair<int,int>(0,0),pair<int,int>(0,1),pair<int,int>(0,2),
                                    pair<int,int>(1,0),pair<int,int>(1,1),pair<int,int>(1,2),
                                    pair<int,int>(2,0),pair<int,int>(2,1),pair<int,int>(2,2)
                                    };
array<array<array<int, 10>, 10>, MAXN> dp; // dp[a][b][c] a번째 인덱스까지 누르는데 손이 b와 c에 있을때 최소 가중치, 

int GetMoveWeight(int num1, int num2){
    if(num1 == num2)
        return 1;
    
    int dr = abs(poses[num1].first - poses[num2].first);
    int dc = abs(poses[num1].second - poses[num2].second);
    int common = min(dr, dc);
    return common * 3 + (dr + dc - common * 2) * 2;
}    

int solution(string numbers) {
    
    fill_n(&dp[0][0][0], MAXN * 10 * 10, INF);
    numbers = " " + numbers;
    
    // dp초기화
    for(int b = 0; b < 10; ++b){
        for(int c = 0; c < 10; ++c){
            dp[0][b][c] = INF;
        }
    }
    dp[0][4][6] = 0;
    
    // dp 계산
    for(int a = 1; a < numbers.size(); ++a){
        int touchTarget = numbers[a] - '0';
        
       
        for(int b = 0; b < 10; ++b){
            for(int c = 0; c < 10; ++c){
                if(b == c)
                    continue;
                
                 // 왼손으로 touchTarget 를 누르는 경우
                if(touchTarget != c && dp[a - 1][b][c] != INF){
                    int weight = dp[a - 1][b][c] + GetMoveWeight(b, touchTarget);
                    dp[a][touchTarget][c] = min(dp[a][touchTarget][c], weight);
                }
                
                // 오른손으로 touchTarget 를 누르는 경우
                if(touchTarget != b && dp[a - 1][b][c] != INF){
                    int weight = dp[a - 1][b][c] + GetMoveWeight(c, touchTarget);
                    dp[a][b][touchTarget] = min(dp[a][b][touchTarget], weight);
                }
                
            }
        }
    }
    
    int ans = INF;
    int lastTarget = numbers[numbers.size() - 1] - '0';
    for(int b = 0; b < 10; ++b){
        for(int c = 0; c < 10; ++c){
            if(dp[numbers.size() - 1][b][c] != INF){
                ans = min(ans, dp[numbers.size() - 1][b][c]);
            }
        }
    }
    
    // 임시 출력
    // for(int b = 0; b < 10; ++b){
    //     for(int c = 0; c < 10; ++c){
    //         cout << "[" << b << "," << c << "] ";
    //         for(int a = 0; a < numbers.size(); ++a){
    //             if(dp[a][b][c] == INF)
    //                 cout << "F ";
    //             else
    //                 cout << dp[a][b][c] << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    
    return ans;
}