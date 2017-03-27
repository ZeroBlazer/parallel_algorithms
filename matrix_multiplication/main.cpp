#include <iostream>
#include <stdio.h>

// #include "linear.h"

using namespace std;

int const /*m = 2,
          r = 3,*/
          n = 500,
          s = 150;

void create_matrix(int **&A, int r, int c) {
    A = new int *[r];
    for(int i=0; i < r; ++i) {
        A[i] = new int[c];
        for(int j=0; j < c; j++)
            A[i][j] = rand()%10;
    }
}

// void print_matrix(auto R) {
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++)
//             cout << R[i][j] << "\t";
//         cout << endl;
//     }
// }

namespace Linear {
    void matrix_mult(auto a, auto b, auto c) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                c[i][j] = 0;
                for (size_t k = 0; k < n; k++)
                    c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

namespace Blocked {
    void matrix_mult(auto a, auto b, auto c) {
        for (size_t i1 = 0; i1 < n/s; i1+=s)
            for (size_t j1 = 0; j1 < n/s; j1+=s)
                for (size_t k1 = 0; k1 < n/s; k1+=s)
                    for (size_t i = i1; i<i1+s && i<n; i++)
                        for (size_t j = j1; j<j1+s && j<n; j++)
                            for (size_t k = k1; k<k1+s && k<n; k++)
                                c[i][j] += a[i][k] * b[k][j];
    }
}

int main() {
    // int A[m][r] = { {2, 3, 1},
    //                 {2, -7, 4}};
    // int B[r][n] = { {3, 4, 5},
    //                 {1, 1, 4},
    //                 {2, 1, 4}};
    // int L_R[m][n],      //Linear result
    //     P_R[m][n];      //Blocked result

    int **A,
        **B,
        **L_R,      //Linear result
        **B_R;      //Blocked result

    create_matrix(A, n, n);
    create_matrix(B, n, n);
    create_matrix(L_R, n, n);
    create_matrix(B_R, n, n);

    cout << "\nLINEAR MULTIPLICATION\n-------------------------\n";
    Linear::matrix_mult(A, B, L_R);
    // print_matrix(L_R);
    cout << "\nBLOCKED MULTIPLICATION\n-------------------------\n";
    Blocked::matrix_mult(A, B, B_R);
    // print_matrix(P_R);
    cout << "\n\nDone ;)" << endl;
    return 0;
}