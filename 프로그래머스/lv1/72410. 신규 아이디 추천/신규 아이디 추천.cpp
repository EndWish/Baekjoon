#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool IsValidChar(char ch){
    if(islower(ch) || isdigit(ch) || ch == '-' || ch == '_' || ch == '.')
        return true;
    return false;
}

string solution(string new_id) {
    // 1단계
    for(char& ch : new_id){
        if(isupper(ch))
            ch = tolower(ch);
    }
    
    // 2단계
    int nDelete = 0;
    for(int i = 0; i < new_id.size(); ++i) {
        if(IsValidChar(new_id[i])) {
            new_id[i - nDelete] = new_id[i];
        }else{
            ++nDelete;
        }
    }
    new_id = new_id.substr(0, new_id.size() - nDelete);
    
    // 3단계
    nDelete = 0;
    for(int i = 0; i < new_id.size(); ++i) {
        if(new_id[i] == '.' && (0 < i && new_id[i - 1] == '.') ) {
            ++nDelete;
        }else{
            new_id[i - nDelete] = new_id[i];
        }
    }
    new_id = new_id.substr(0, new_id.size() - nDelete);
    
    // 4단계
    if(new_id[0] == '.')
        new_id = new_id.substr(1, new_id.size() - 1);
    if(new_id[new_id.size() - 1] == '.')
        new_id = new_id.substr(0, new_id.size() - 1);
    
    // 5단계
    if(new_id.size() == 0)
        new_id.push_back('a');
    
    // 6단계
    if(16 <= new_id.size())
        new_id = new_id.substr(0, 15);
        if(new_id[new_id.size() - 1] == '.')
        new_id = new_id.substr(0, new_id.size() - 1);
    
    // 7단계
    while(new_id.size() <= 2)
        new_id.push_back(new_id.back());
    
    return new_id;
}
