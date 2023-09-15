#include <string>
#include <vector>
#include <array>
#include <numeric>
#include <iostream>

using namespace std;

#define INF numeric_limits<int>::max()

array<int, 5> dr = {0, -1, 1, 0, 0};
array<int, 5> dc = {0, 0, 0, -1, 1};
int n;
array<int, 8> starting;

bool IsInside(int r, int c){
    return 0 <= r && r < n && 0 <= c && c < n;
}

void Rotation(int r, int c, int count, vector<vector<int>>& clockHands){
    for(int i = 0; i < 5; ++i){
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if(IsInside(nr, nc)){
            clockHands[nr][nc] += count;
            clockHands[nr][nc] %= 4;
        }
    }
    
}

int BruteForce(vector<vector<int>> clockHands){
    int ans = 0;
    
    // 첫줄을 회전시켜본다.
    for(int i = 0; i < n; ++i){
        Rotation(0, i, starting[i], clockHands);
        ans += starting[i];
    }
    
    for(int r = 1; r < n; r++){
        for(int c = 0; c < n; c++){
            if(clockHands[r - 1][c] != 0){
                ans += 4 - clockHands[r - 1][c];
                Rotation(r, c, 4 - clockHands[r - 1][c], clockHands);
            }
        }
    }
    
    for(int c = 0; c < n; ++c){
        if(clockHands[n - 1][c] != 0)
            return INF;
    }
    
    return ans;
}

int DFS(int pos, vector<vector<int>>& clockHands){
    if(pos == n){
        return BruteForce(clockHands);
    }
    
    int ans = INF;
    for(int i = 0; i < 4; ++i){
        starting[pos] = i;
        ans = min(ans, DFS(pos + 1, clockHands));
    }
    
    return ans;
}



int solution(vector<vector<int>> clockHands) {
    n = clockHands.size();
    
    return DFS(0, clockHands);
    

}