#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

#define Puzzle vector<pair<int,int>>

array<int, 4> dr = {0,0,-1,1};
array<int, 4> dc = {-1,1,0,0};

int n, m;

bool IsInside(int r, int c){
    return 0 <= r && r < n && 0 <= c && c < m;
}

void DFS(int r, int c, int cr, int cc, Puzzle& puzzle, vector<vector<int>>& board, int targetType) {
    board[r][c] = (targetType + 1) % 2;
    puzzle.push_back({r - cr, c - cc});
    
    for(int i = 0; i < 4; ++i){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!IsInside(nr, nc) || board[nr][nc] != targetType)
            continue;
        DFS(nr, nc, cr, cc, puzzle, board, targetType);
    }
}

void Rotate(Puzzle& puzzle){
    for(auto& [r, c] : puzzle){
        swap(r, c);
        c = -c;
    }
    sort(puzzle.begin(), puzzle.end());
    auto [cr, cc] = puzzle[0];
    for(auto& [r, c] : puzzle){
        r -= cr;
        c -= cc;
    }
}

bool IsSamePuzzle(Puzzle& a, Puzzle& b){
    sort(a.begin(), a.end());
    for(int i = 0; i < 4; ++i) {
        Rotate(b);
        if(a == b)
            return true;
    }
    return false;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    n = game_board.size();
    m = game_board[0].size();
    
    // 구멍들을 구한다.
    vector<Puzzle> holes;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < m; ++c){
            if(game_board[r][c] == 0){
                Puzzle hole;
                DFS(r, c, r, c, hole, game_board, 0);
                holes.push_back(move(hole));
            }  
        }
    }
    
    // 퍼즐들을 구한다.
    vector<Puzzle> puzzles;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < m; ++c){
            if(table[r][c] == 1){
                Puzzle puzzle;
                DFS(r, c, r, c, puzzle, table, 1);
                puzzles.push_back(move(puzzle));
            }
        }
    }
    
    // 끼울수 있는 퍼즐들을 찾는다.
    //cout << holes.size() << endl;
    //cout << puzzles.size() << endl;
    
    int ans = 0;
    vector<bool> finish(puzzles.size(), false);
    for(Puzzle hole : holes){
        for(int i = 0; i < puzzles.size(); ++i){
            if(finish[i])
                continue;
            
            if(IsSamePuzzle(hole, puzzles[i])){
                ans += hole.size();
                //cout << hole.size() << "개 추가\n";
                finish[i] = true;
                break;
            }
        }
    }
    
    return ans;
}




