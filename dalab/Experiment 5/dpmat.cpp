#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printOptimalParenthesization(const vector<vector<int>>& s, int i, int j);


void matrixChainOrder(const vector<int>& dims) {
    int n = dims.size() - 1;
    
    
    vector<vector<int>> m(n, vector<int>(n, 0));

    vector<vector<int>> s(n, vector<int>(n, 0));

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            
           
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    
    cout << "Minimum number of multiplications: " << m[0][n-1] << endl;
    

    cout << "Optimal Parenthesization: ";
    printOptimalParenthesization(s, 0, n-1);
    cout << endl;
}


void printOptimalParenthesization(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i+1;
    } else {
        cout << "(";
        printOptimalParenthesization(s, i, s[i][j]);
        printOptimalParenthesization(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
   
    vector<int> dims = {10, 20, 30, 40, 30};

    matrixChainOrder(dims);
    return 0;
}

