#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 公共接口：解数独
    void solveSudoku(vector<vector<char>>& board) {

    }
    // 公共接口：判断数独是否有效
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; ++i)
            if(invalid_row(board, i) || invalid_col(board, i) || invalid_subbox(board, i))
                return false;
        return true;
    }
private:
    bool invalid_row(const vector<vector<char>>& board, int r) {
        vector<int> count_(9, 0);
        for(int j = 0; j < 9; j++) {
            if('.' == board[r][j]) continue;
            ++count_[board[r][j]-'1'];
            if(count_[board[r][j]-'1'] > 1) return true;
        }
        return false;
    }
    bool invalid_col(const vector<vector<char>>& board, int c) {
        vector<int> count_(9, 0);
        for(int i = 0; i < 9; i++) {
            if('.' == board[i][c]) continue;
            ++count_[board[i][c]-'1'];
            if(count_[board[i][c]-'1'] > 1) return true;
        }
        return false;
    }
    bool invalid_subbox(const vector<vector<char>>& board, int b) {
        vector<int> count_(9, 0);
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                char ch = board[xy[b][0]+i][xy[b][1]+j];
                if('.' == ch) continue;
                ++count_[ch-'1'];
                if(count_[ch-'1'] > 1) return true;
            }
        }
        return false;
    }
private:
    int xy[9][2] = {
        {0,0}, {0,3}, {0,6},
        {3,0}, {3,3}, {3,6},
        {6,0}, {6,3}, {6,6}
    };
};


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}