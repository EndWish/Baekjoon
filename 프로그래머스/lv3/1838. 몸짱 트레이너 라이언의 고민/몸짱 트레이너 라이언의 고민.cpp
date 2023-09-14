#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#include <iostream>

using namespace std;

bool IsInside(int r, int c, int n);
bool Setting(int n, int nPeople, int length);

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, int m, vector<vector<int>> timetable) {
    
    sort(timetable.begin(), timetable.end(), [](vector<int>& a, vector<int>& b){
        if(a[0] == b[0])
            return a[1] < b[1];
        return a[0] < b[0];
    });
    
    int maxPeople = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 0; i < timetable.size(); ++i){
        while(!pq.empty() && pq.top() < timetable[i][0] )
            pq.pop();
        
        pq.push(timetable[i][1]);
        maxPeople = max(maxPeople, (int)pq.size());
    }
    
    if(maxPeople == 1)
        return 0;
    
    for(int i = n * 2; i > 0; --i){
        if(Setting(n, maxPeople, i))
            return i;
    }
}

bool Setting(int n, int nPeople, int length){
    for(int offset = 0; offset < min(length, n); ++offset){
        vector<vector<bool>> board(n, vector<bool>(n, false));
    
        int settingNum = 0;
        for(int r = 0; r < n; ++r){
            for(int c = 0; c < n; ++c){
                if(r == 0 && c == 0)
                    c = offset;
                
                if(!board[r][c]){
                    ++settingNum;
                    for(int dr = -length + 1; dr < length; ++dr){
                        for(int dc = -length + 1; dc < length; ++dc){
                            int nr = r + dr;
                            int nc = c + dc;
                            if(IsInside(nr, nc, n) && abs(dr) + abs(dc) < length)
                                board[nr][nc] = true;
                        }
                    }
                    if(nPeople == settingNum)
                    return true;
                }
            }
        }
    }
    
    
    return false;
}

bool IsInside(int r, int c, int n){
    return 0 <= r && r < n && 0 <= c && c < n;
}
