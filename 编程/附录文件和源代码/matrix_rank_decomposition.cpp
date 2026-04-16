#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, vector<double>(cols, 0.0)) {}
    
    Matrix(const vector<vector<double>>& input) : data(input), rows(input.size()), cols(input[0].size()) {}
    
    void set(int i, int j, double value) {
        data[i][j] = value;
    }
    
    double get(int i, int j) const {
        return data[i][j];
    }
    
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << setw(10) << fixed << setprecision(2) << data[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    int rank() const {
        Matrix temp(*this);
        int r = 0;
        
        for (int col = 0; col < cols && r < rows; ++col) {
            int pivot_row = r;
            for (int row = r; row < rows; ++row) {
                if (abs(temp.get(row, col)) > abs(temp.get(pivot_row, col))) {
                    pivot_row = row;
                }
            }
            
            if (abs(temp.get(pivot_row, col)) < 1e-10) {
                continue;
            }
            
            temp.swapRows(r, pivot_row);
            
            double pivot_value = temp.get(r, col);
            if (abs(pivot_value) > 1e-10) {
                ++r;
            }
        }
        
        return r;
    }
    
    void swapRows(int i, int j) {
        swap(data[i], data[j]);
    }
    
    pair<Matrix, Matrix> fullRankDecomposition() const {
        int r = rank();
        Matrix B(rows, r);
        Matrix C(r, cols);
        
        // 直接使用原矩阵的列空间构建B和C
        // 对于秩为1的特殊情况，直接分解为列向量乘以行向量
        if (r == 1) {
            // 对于秩1矩阵，取第一列为B的列，其余元素为1
            for (int i = 0; i < rows; ++i) {
                B.set(i, 0, data[i][0]);
            }
            
            double scale = 1.0 / data[0][0];
            for (int j = 0; j < cols; ++j) {
                C.set(0, j, data[0][j] * scale);
            }
            
            return make_pair(B, C);
        }
        
        Matrix temp(*this);
        vector<int> pivot_cols;
        int current_rank = 0;
        
        // 执行行变换，得到行阶梯形
        for (int col = 0; col < cols && current_rank < r; ++col) {
            // 找到主元行
            int pivot_row = current_rank;
            for (int row = current_rank; row < rows; ++row) {
                if (abs(temp.get(row, col)) > abs(temp.get(pivot_row, col))) {
                    pivot_row = row;
                }
            }
            
            if (abs(temp.get(pivot_row, col)) < 1e-10) {
                continue;
            }
            
            // 交换行
            temp.swapRows(current_rank, pivot_row);
            pivot_cols.push_back(col);
            
            // 将主元归一化为1
            double pivot_value = temp.get(current_rank, col);
            for (int j = col; j < cols; ++j) {
                temp.data[current_rank][j] /= pivot_value;
            }
            
            // 消去主元列的其他元素
            for (int row = 0; row < rows; ++row) {
                if (row != current_rank && abs(temp.get(row, col)) > 1e-10) {
                    double factor = temp.get(row, col);
                    for (int j = col; j < cols; ++j) {
                        temp.data[row][j] -= factor * temp.data[current_rank][j];
                    }
                }
            }
            
            ++current_rank;
        }
        
        // 构建B：原矩阵的列空间基
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < r; ++j) {
                B.set(i, j, data[i][pivot_cols[j]]);
            }
        }
        
        // 构建C：行最简形的前r行
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < cols; ++j) {
                C.set(i, j, temp.get(i, j));
            }
        }
        
        return make_pair(B, C);
    }