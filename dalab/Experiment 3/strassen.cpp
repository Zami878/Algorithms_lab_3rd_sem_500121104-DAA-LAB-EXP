#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;


vector<vector<int>> generateRandomMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10; 
        }
    }
    return matrix;
}

// Function for traditional matrix multiplication
void traditionalMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


void subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassenMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        vector<vector<int>> A11(newSize, vector<int>(newSize)),
            A12(newSize, vector<int>(newSize)),
            A21(newSize, vector<int>(newSize)),
            A22(newSize, vector<int>(newSize)),
            B11(newSize, vector<int>(newSize)),
            B12(newSize, vector<int>(newSize)),
            B21(newSize, vector<int>(newSize)),
            B22(newSize, vector<int>(newSize)),
            C11(newSize, vector<int>(newSize)),
            C12(newSize, vector<int>(newSize)),
            C21(newSize, vector<int>(newSize)),
            C22(newSize, vector<int>(newSize)),
            M1(newSize, vector<int>(newSize)),
            M2(newSize, vector<int>(newSize)),
            M3(newSize, vector<int>(newSize)),
            M4(newSize, vector<int>(newSize)),
            M5(newSize, vector<int>(newSize)),
            M6(newSize, vector<int>(newSize)),
            M7(newSize, vector<int>(newSize)),
            temp1(newSize, vector<int>(newSize)),
            temp2(newSize, vector<int>(newSize));

        // Divide matrices A and B into submatrices
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

       
        addMatrices(A11, A22, temp1);
        addMatrices(B11, B22, temp2);
        strassenMatrixMultiplication(temp1, temp2, M1);

        addMatrices(A21, A22, temp1);
        strassenMatrixMultiplication(temp1, B11, M2);

        subtractMatrices(B12, B22, temp2);
        strassenMatrixMultiplication(A11, temp2, M3);

        subtractMatrices(B21, B11, temp2);
        strassenMatrixMultiplication(A22, temp2, M4);

        addMatrices(A11, A12, temp1);
        strassenMatrixMultiplication(temp1, B22, M5);

        subtractMatrices(A21, A11, temp1);
        addMatrices(B11, B12, temp2);
        strassenMatrixMultiplication(temp1, temp2, M6);

        subtractMatrices(A12, A22, temp1);
        addMatrices(B21, B22, temp2);
        strassenMatrixMultiplication(temp1, temp2, M7);

        
        addMatrices(M1, M4, temp1);
        subtractMatrices(temp1, M5, temp2);
        addMatrices(temp2, M7, C11);

        addMatrices(M3, M5, C12);

        addMatrices(M2, M4, C21);

        addMatrices(M1, M3, temp1);
        subtractMatrices(temp1, M2, temp2);
        addMatrices(temp2, M6, C22);

        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
}

int main() {
    vector<int> test_sizes = {128, 256, 512, 1024, 2048}; 
    
    for (int n : test_sizes) {
        
        vector<vector<int>> A = generateRandomMatrix(n);
        vector<vector<int>> B = generateRandomMatrix(n);
        vector<vector<int>> C(n, vector<int>(n)); // Result matrix

        // Measure traditional matrix multiplication time
        auto start = high_resolution_clock::now();
        traditionalMatrixMultiplication(A, B, C);
        auto end = high_resolution_clock::now();
        auto durationTraditional = duration_cast<milliseconds>(end - start);
        cout << "Test Size: " << n << " | Traditional Time: " << durationTraditional.count() << " milliseconds" << endl;

        // Measure Strassen matrix multiplication time
        start = high_resolution_clock::now();
        strassenMatrixMultiplication(A, B, C);
        end = high_resolution_clock::now();
        auto durationStrassen = duration_cast<milliseconds>(end - start);
        cout << "Test Size: " << n << " | Strassen Time: " << durationStrassen.count() << " milliseconds" << endl;
    }
    
    return 0;
}

