#ifndef matrix_h
#define matrix_h
#include <fstream>
#include <string.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <typeinfo>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Matrix{
public:
    int **elem;
    int rows , cols;
    Matrix(int n, int m);
    Matrix(std::string s);
    Matrix(Matrix &A, int N);
    Matrix(Matrix &A, int N, int K);
    Matrix();
    friend Matrix operator *(Matrix &A, Matrix &B);
    friend Matrix operator %(Matrix &A, Matrix &B);
    friend std::ostream& operator << (std::ostream& stream, Matrix M);
    void Random_permutate();
    void RREF(Matrix &A);
    void COPY(Matrix &A);
    void PRINT();
    void Last_cols_permutation();
    void First_cols_permutation();
    bool Full_rank();
    int Ham_weight();
    ~Matrix();
};

#endif
