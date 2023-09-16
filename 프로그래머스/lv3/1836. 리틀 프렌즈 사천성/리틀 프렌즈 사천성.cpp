#include <string>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

#define MAXN 101

array<array<pair<int,int>, 2>, 26> alphabets;
int count;

int dr[] = {0,-1,0,1};
int dc[] = {-1,0,1,0};
int ndir[] = {0,1,2,3};

bool IsInside(int r, int c, vector<string>& board){
    return 0 <= r && r < board.size() && 0 <= c && c < board[0].size();
}

bool DFS(int r, int c, int index, int turn, int dir, vector<string>& board){
    //cout << "index : " << (char)(index + 'A') << ", pos : " << r << ", " << c << endl;
    if(make_pair(r, c) == alphabets[index][1])
        return true;
    
    for(int i = 0; i < 4; ++i){
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        // 반대 방향일 경우 제외
        if(ndir[i] == (dir + 2) % 4)
            continue;
        
        // 가지 못하는 곳일 경우 제외
        if(!IsInside(nr,nc, board) || 
           !((board[nr][nc] == 'A' + index) || board[nr][nc] == '.'))
            continue;
        
        // 같은 방향일 경우
        if(dir == ndir[i]) {
            bool ans = DFS(nr, nc, index, turn, ndir[i], board);
            if(ans)
                return true;
        }
        // 다른 방향일 경우
        else{
            if(turn == 0){
                bool ans = DFS(nr, nc, index, turn + 1, ndir[i], board);
                if(ans)
                    return true;
            } 
        }
    }
    
    return false;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    fill_n(&alphabets[0][0], 26 * 2, make_pair(-1,-1));
    count = 0;
    
    for(int r= 0; r < m; ++r){
        for(int c = 0; c < n; ++c){
            char ch = board[r][c];
            if(isalpha(ch)){
                if(alphabets[ch - 'A'][0] == make_pair(-1,-1)){
                    alphabets[ch - 'A'][0] = make_pair(r, c);
                    ++count;
                }else{
                    alphabets[ch - 'A'][1] = make_pair(r, c);
                }
            }
        }
    }
    
    string ans;
    
    for(int i = 0; i < count; ++i){
        // 사전순으로 알파벳을 제거한다.
        bool clear = false;
        for(int index = 0; index < 26; ++index){
            if(alphabets[index][0] == make_pair(-1,-1))
                continue;
            
            // 알파벳을 제거할 수 있는지 확인한다.
            auto [r, c] = alphabets[index][0];
            
            for(int dir = 0; dir < 4; ++dir){
                if(DFS(r, c, index, 0, dir, board)){
                    // 알파벳을 제거하고 break
                    board[alphabets[index][0].first][alphabets[index][0].second] = '.';
                    board[alphabets[index][1].first][alphabets[index][1].second] = '.';
                    alphabets[index][0] = make_pair(-1,-1);
                    alphabets[index][1] = make_pair(-1,-1);
                    
                    clear = true;
                    ans.push_back(index + 'A');
                    break;
                }
            }
            if(clear)
                break;
        }
        
        if(!clear){
            cout << "답 : " << ans << endl;
            return "IMPOSSIBLE";
        }
    }
    
    
    
    return ans;
}