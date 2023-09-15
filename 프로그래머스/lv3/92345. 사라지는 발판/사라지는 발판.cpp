#include <string>
#include <vector>
#include <numeric>
#include <array>
#include <iostream>

using namespace std;

#define INF numeric_limits<int>::max()

array<int, 4> dr = {0,0,1,-1};
array<int, 4> dc = {1,-1,0,0};
int n, m;

bool IsInside(int r, int c){
    return 0 <= r && r < n && 0 <= c && c < m;
}

pair<int, int> DFS(vector<pair<int,int>>& poses, int turn, int nMove, vector<vector<int>>& board){
    int r = poses[turn].first;
    int c = poses[turn].second;
    int other = (turn + 1) % 2;
    
    // 승패판단
    if(board[r][c] == 0){
        return {other, nMove};  // 상대방의 승리
    }
    
    bool canMove = false;
    pair<int,int> ans = {other, 0};
    for(int i = 0; i < 4; ++i){

        int nr = poses[turn].first + dr[i];
        int nc = poses[turn].second + dc[i];
        
        if(!IsInside(nr, nc) || board[nr][nc] == 0)
            continue;
        
        canMove = true;
        poses[turn].first = nr;
        poses[turn].second = nc;
        board[r][c] = 0;
        ++nMove;
        
        // DFS 수행
        auto [winner, move] = DFS(poses, (turn + 1) % 2, nMove, board);
        if(winner == turn){ // 내가 최대한 빨리 이길수 있는 경우로 이동한다.
            if(ans.first != winner){
                ans.second = move;
            }else{
                ans.second = min(ans.second, move);
            }
            ans.first = turn;
        } else if(ans.first == other){  // 내가 지는 경우 최대한 버티는 쪽으로
            ans.second = max(ans.second, move);
        }
        
        // 원상복구
        poses[turn].first = r;
        poses[turn].second = c;
        board[r][c] = 1;
        --nMove;
    }
    
    if(!canMove){
        return {other, nMove};
    }
    else{
        return ans;
    }
        
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    n = board.size();
    m = board[0].size();
    
    vector<pair<int,int>> poses = { pair<int,int>{aloc[0], aloc[1]},
                                  pair<int,int>{bloc[0], bloc[1]}};
    
    return DFS(poses, 0, 0, board).second;
}