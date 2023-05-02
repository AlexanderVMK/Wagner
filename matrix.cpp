#include "matrix.h"

template <typename T>
void swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

Matrix::Matrix(){}

//Construct 1 matrix
Matrix::Matrix(int n, int m)
{
    rows = n;
    cols = m;
    elem = new int *[rows];
    for(int i = 0; i < rows; i++)
    {
        elem[i] = new int [cols];
        for(int j = 0; j < cols; j++)
        {
            if(i == j){
                elem[i][j] = 1;
            }else{
                elem[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix(Matrix &A, int N)
{
    rows = 1;
    cols = N;
    elem = new int *[rows];
    for(int i = 0; i < rows; i++)
    {
        elem[i] = new int [cols];
        for(int j = 0; j < cols; j++){
            elem[i][j] = 0; 
        }
    }
    for(int i = 0; i < A.rows; i++){
        elem[0][N - A.rows + i] = A.elem[i][0];
    }
}

//Matrix = cols N to K of Matrix A
Matrix::Matrix(Matrix &A, int N, int K)
{
    rows = A.rows;
    cols = K - N + 1;
    for(int i = 0; i < rows; i++)
    {
        elem[i] = new int [cols];
        for(int j = 0; j < cols; j++)
        {
            elem[i][j] = A.elem[i][j+N];
        }
    }
}

//Reading matrix from file (first line - rows_number space cols_number)
Matrix::Matrix(std::string s)
{
    int n = 0, m = 0;
    std::ifstream in;
    in.open(s);
    in >> n >> m;
    rows = n;
    cols = m;
    elem = new int *[rows];
    for(int i = 0; i < rows; i++)
    {
        elem[i] = new int [cols];
        for(int j = 0; j < cols; j++){
            in >> elem[i][j]; 
        }
    }
}


void Matrix::PRINT()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << elem[i][j] << " "; 
        }
        std::cout << std::endl;
    }
}


//Random permutation
void Matrix::Random_permutate()
{
    for (int i = 0; i < rows; i++)
    {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, rows-1);
        int x = distribution(generator);
        swap(&elem[i], &elem[(x)]);
    }
}

//Matrix N x M (N < M); Place last M - N cols on first M - N positions.
void Matrix::Last_cols_permutation()
{
    if((cols - (2 * rows)) < 0)
    {
        for(int i = 0; i < rows; i++)
        {
            int * tmp;
            tmp = new int [cols - rows];
            for(int j = 0; j < cols - rows; j++)
            {
                tmp[j] = elem[i][j];
            }
            
            for(int j = 0; j < rows; j++)
            {
                elem[i][j] = elem[i][cols - rows + j];
            }

            for(int j = 0; j < cols - rows; j++)
            {
                elem[i][rows + j] = tmp[j];
            }
            delete [] tmp;
        }
    }else
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols - rows; j++)
            {
                elem[i][j] += elem[i][j + cols - rows];
                elem[i][j + cols - rows] = elem[i][j] - elem[i][j + cols - rows];
                elem[i][j] -= elem[i][j + cols - rows];
            }
        }
    }
} 

//Matrix N x M (N < M); Place first M - N cols on last M - N positions.
void Matrix::First_cols_permutation(){
    if((cols - (2 * rows)) < 0)
    {
        for(int i = 0; i < rows; i++)
        {
            int * tmp;
            tmp = new int [cols - rows];
            for(int j = 0; j < cols - rows; j++)
            {
                tmp[j] = elem[i][rows + j];
            }
            
            for(int j = 0; j < rows; j++)
            {
                elem[i][cols-1-j] = elem[i][rows-1-j];
            }

            for(int j = 0; j < cols - rows; j++)
            {
                elem[i][j] = tmp[j];
            }
            delete [] tmp;
        }
    }else
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols - rows; j++)
            {
                elem[i][j] += elem[i][j + cols - rows];
                elem[i][j + cols - rows] = elem[i][j] - elem[i][j + cols - rows];
                elem[i][j] -= elem[i][j + cols - rows];
            }
        }
    }
}

//DEEP COPY THIS := A
void Matrix::COPY(Matrix &A){
    for(int i = 0; i < rows; i++)
    {
        delete[] elem[i];
    }
    delete[] elem;

    rows = A.rows;
    cols = A.cols;
    elem = new int *[rows];
    for(int i = 0; i < rows; i++)
    {
        elem[i] = new int [cols];
        for(int j = 0; j < cols; j++)
        {
            elem[i][j] = A.elem[i][j];
        }
    }
}

//Matrix ordinary multiply: C := A * B
Matrix operator *(Matrix &A, Matrix &B)
{
    int Acols = A.cols, Arows = A.rows, Brows = B.rows, Bcols = B.cols;
    Matrix C(Arows, Bcols);
    if( Acols == Brows)
    {
        for(int i = 0; i < Arows; i++)
        {
            for(int j = 0; j < Bcols; j++)
            {
                int tmp = 0;
                for(int k = 0; k < Acols; k++)
                {
                    tmp += A.elem[i][k] * B.elem[k][j];
                }
                C.elem[i][j] = tmp % 3;
            }
        }
    }
    return C;
}

//Operator for multiplying a matrix by a transposed matrix: C := A * B^T
Matrix operator %(Matrix &A, Matrix &B)
{
    int Acols = A.cols, Arows = A.rows, Brows = B.rows, Bcols = B.cols; 
    Matrix C(Arows, Brows);
    if( Acols == Bcols)
    {
        for(int i = 0; i < Arows; i++)
        {
            for(int j = 0; j < Brows; j++)
            {
                int tmp = 0;
                for(int k = 0; k < Acols; k++)
                {
                    tmp += A.elem[i][k] * B.elem[j][k];
                }
                C.elem[i][j] = tmp;
            }
        }
    }
    return C;
}

//Matrix output
std::ostream& operator << (std::ostream& stream, Matrix matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            stream << matrix.elem[i][j] << " "; 
        }
        stream << std::endl;
    }
    return stream;
}

//Reduced row echelon form
void Matrix::RREF(Matrix &A){
    int l = 0;
    int r = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            A.elem[i][j] = i == j ? 1 : 0;
        }
    }

    for(int i = 0; i < rows; i++)
    {
        if(cols <= l) return void();
        r = i;
        while(elem[r][l] == 0)
        {
            r++;
            if(rows == r){
                r = i;
                l++;
                if(cols == l) return void();
            }
        }

        if(i not_eq r)
        {
            swap(&elem[r],&elem[i]);
            swap(&A.elem[r],&A.elem[i]);
        }
        
        int lead = elem[i][l];
        for(int t = 0; t < cols; t++)
        {
            elem[i][t] = (elem[i][t] * lead) % 3;
            if(t < rows){
                A.elem[i][t] = (A.elem[i][t] * lead) % 3;
            }
        }

        for(int t = 0; t < rows; t++)
        {
            if(t != i)
            {
                int sub = elem[t][l];
                for(int k = 0; k < cols; k++)
                {
                    elem[t][k] = (elem[t][k] - elem[i][k] * sub) % 3;
                    if(elem[t][k] < 0) elem[t][k] += 3;
                    if(k < rows){
                        A.elem[t][k] = (A.elem[t][k] - A.elem[i][k] * sub) % 3;
                        if(A.elem[t][k] < 0) A.elem[t][k] += 3;
                    }
                }
            }
        }
        l++;
    }

} 

bool Matrix::Full_rank(){
    for(int i = 0; i < rows; i++)
        if(elem[i][i] == 0) return false;
    return true;
}

int Matrix::Ham_weight(){
    int w = 0;
    if(cols == 1 or rows == 1)
        for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(elem[i][j]) w++;
    return w;
}

Matrix::~Matrix()
{
    for(int i = 0; i < rows; i++)
    {
        delete[] elem[i];
    }
    delete[] elem;
}
