#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <queue>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()
#define MAXK 5

array<int, MAXK> settings;

int Calculation(int k, vector<vector<int>>& reqs){
    vector<priority_queue<int, vector<int>, greater<int>>> endTimes(k);
    for(int i = 0; i < k; ++i){
        for(int j = 0; j < settings[i]; ++j){
            endTimes[i].push(0);
        }
    }
    
    int ans = 0;
    for(int i = 0; i < reqs.size(); ++i) {
        int type = reqs[i][2] - 1;
        int startTime = reqs[i][0];
        int min = reqs[i][1];
        
        int endTime = endTimes[type].top();
        if(endTime < startTime){
            endTimes[type].pop();
            endTimes[type].push(startTime + min);
        }else{
            ans += endTime - startTime;
            endTimes[type].pop();
            endTimes[type].push(endTime + min);
        }
    }
    
    return ans;
}

int DFS(int pos, int spare, int k, vector<vector<int>>& reqs){
    if(spare == 0)
        return INF;
    
    if(pos == k - 1){
        settings[pos] = spare;
        // 몇분이 걸리는지 계산하여 리턴한다.
        return Calculation(k, reqs);
    }
    
    int ans = INF;
    for(int i = 1; i <= spare; ++i){
        settings[pos] = i;
        ans = min(ans, DFS(pos + 1, spare - i, k, reqs) );
    }
    return ans;
}

int solution(int k, int n, vector<vector<int>> reqs) {
    // reqs를 요청시간순으로 정렬한다.
    return DFS(0, n, k, reqs);
}