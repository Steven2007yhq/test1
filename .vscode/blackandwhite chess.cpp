#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

const int N = 6;
vector<vector<int>> board = {
    {1, 0, -1, -1, 0, -1},
    {-1, -1, -1, 0, -1, -1},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, -1, -1},
    {-1, -1, 1, -1, -1, 1},
    {-1, 0, -1, -1, 1, -1}
};

unordered_set<string> row_set;
unordered_set<string> col_set;

// 检查在 (r, c) 位置放置 v 是否合法
bool is_valid(int r, int c, int v) {
    // 检查行内连续三个相同
    if (c >= 2 && board[r][c-1] == v && board[r][c-2] == v) return false;
    // 检查列内连续三个相同
    if (r >= 2 && board[r-1][c] == v && board[r-2][c] == v) return false;
    
    // 检查行内黑棋数量不超过3
    int row_black = 0;
    for (int j = 0; j < N; ++j) {
        if (board[r][j] == 1) row_black++;
        if (j == c && v == 1) row_black++;
    }
    if (row_black > 3) return false;
    
    // 检查列内黑棋数量不超过3
    int col_black = 0;
    for (int i = 0; i < N; ++i) {
        if (board[i][c] == 1) col_black++;
        if (i == r && v == 1) col_black++;
    }
    if (col_black > 3) return false;
    
    return true;
}

// 检查所有列是否唯一
bool check_cols_unique() {
    unordered_set<string> s;
    for (int c = 0; c < N; ++c) {
        string col;
        for (int r = 0; r < N; ++r) {
            col += (board[r][c] + '0');
        }
        if (s.count(col)) return false;
        s.insert(col);
    }
    return true;
}

bool backtrack(int pos) {
    if (pos == N * N) {
        return check_cols_unique();
    }
    int r = pos / N;
    int c = pos % N;
    
    if (board[r][c] != -1) {
        return backtrack(pos + 1);
    }
    
    for (int v : {0, 1}) {
        if (is_valid(r, c, v)) {
            board[r][c] = v;
            
            // 如果是行末，检查行是否唯一
            if (c == N - 1) {
                string row;
                for (int j = 0; j < N; ++j) row += (board[r][j] + '0');
                if (row_set.count(row)) {
                    board[r][c] = -1;
                    continue;
                }
                row_set.insert(row);
            }
            
            if (backtrack(pos + 1)) {
                return true;
            }
            
            // 回溯
            if (c == N - 1) {
                string row;
                for (int j = 0; j < N; ++j) row += (board[r][j] + '0');
                row_set.erase(row);
            }
            board[r][c] = -1;
        }
    }
    return false;
}

int main() {
    // 初始化行集合
    for (int r = 0; r < N; ++r) {
        bool complete = true;
        string row;
        for (int c = 0; c < N; ++c) {
            if (board[r][c] == -1) {
                complete = false;
                break;
            }
            row += (board[r][c] + '0');
        }
        if (complete) {
            row_set.insert(row);
        }
    }
    
    if (backtrack(0)) {
        string result;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                result += (board[r][c] + '0');
            }
        }
        cout << result << endl;
    }
    return 0;
}