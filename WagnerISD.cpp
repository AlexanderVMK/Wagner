#include "matrix.h"
int main(int argc, char const *argv[]){
    if(argc == 4){
        std::string H_file = argv[1], s_file = argv[2], e_weight = argv[3];
        int weight = stoi(e_weight);
        try{
            Matrix H(H_file);
            Matrix s(s_file);
            int N_H = 4;
            int wN = weight / N_H;
            int N_cols = H.cols / 4;
            Matrix * Arr_H = new Matrix [N_H];
            
            // H = [H1][H2][H3][H4]
            Matrix TMP(H.rows, N_cols);
            for(int i = 0; i < N_H; i++)
            {
                Arr_H[i].rows = Arr_H[i].cols = 0;
                Arr_H[i].COPY(TMP);
            }
            for(int i = 0; i < H.rows; i++)
            for(int j = 0; j < H.cols; j++)
            {
                Arr_H[j / N_cols].elem[i][j % N_cols] = H.elem[i][j];
            }

            int L = pow(3, H.rows / 2);
            std::cout << " L1 L2 S1 S2 making " << std::endl;
            //L1 init
            int** L1 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                L1[i] = new int [N_cols];
            }
            std::cout << " L2 S1 S2 making " << std::endl;
            //S1 init
            int** S1 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                S1[i] = new int [H.rows];
            }
            std::cout << " S1 S2 making " << std::endl;
            //L2 init
            int** L2 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                L2[i] = new int [N_cols];
            }
            std::cout << " S2 making " << std::endl;
            //S2 init
            int** S2 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                S2[i] = new int [H.rows];
            }
            std::cout << " L1 L2 S1 S2 creating " << std::endl;
            //L1 and L2 creater
            for(int i = 0; i < L; i++)
            for(int j = 0; j < wN; j++)
            {
                std::random_device random_device;
                std::mt19937 generator(random_device());
                std::uniform_int_distribution<> distribution(1, 2);
                L1[i][j] = distribution(generator);
                L2[i][j] = distribution(generator);
            }
            for(int i = 0; i < L; i++)
            for(int j = 0; j < N_cols; j++)
            {
                std::random_device random_device;
                std::mt19937 generator(random_device());
                std::uniform_int_distribution<> distribution(0, N_cols-1);
                int x = distribution(generator);
                int t = L1[i][x];
                L1[i][x] = L1[i][j];
                L1[i][j] = t;
            }

            for(int i = 0; i < L; i++)
            for(int j = 0; j < N_cols; j++)
            {
                std::random_device random_device;
                std::mt19937 generator(random_device());
                std::uniform_int_distribution<> distribution(0, N_cols-1);
                int x = distribution(generator);
                int t = L2[i][x];
                L2[i][x] = L2[i][j];
                L2[i][j] = t;
            }
            
            //S1 creater
            for(int i = 0; i < L; i++)
            for(int j = 0; j < H.rows; j++)
            {
                int sum = 0;
                for(int k = 0; k < N_cols; k++){
                    sum += L1[i][k] * Arr_H[0].elem[j][k];
                }
                S1[i][j] = sum % 3;
            }

            //S2 creater
            for(int i = 0; i < L; i++)
            for(int j = 0; j < H.rows; j++)
            {
                int sum = 0;
                for(int k = 0; k < N_cols; k++){
                    sum += L2[i][k] * Arr_H[1].elem[j][k];
                }
                S2[i][j] = sum % 3;
            }
            //S12 init
             int** S12 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                S12[i] = new int [H.rows];
            }

            //L12 init
            int** L12 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                L12[i] = new int [2 * N_cols];
            }

            std::cout << " L12 S12 making " << std::endl;
            //L12 and S12 creater
            int KOL = 0;
            for(int i = 0; i < L; i++)
            {
                for(int j = 0; j < L; j++)
                {
                    int tm = true;
                    for(int k = H.rows / 2; k < H.rows; k++)
                    {
                        if((S1[i][k]+S2[j][k]) % 3 != 0) tm = false;
                    }
                    if(tm)
                    {
                        for(int h = 0; h < H.rows; h++)
                        {
                            S12[KOL][h] = (S1[i][h] + S2[j][h]) % 3;
                        }
                        for(int h = 0; h < N_cols; h++)
                            L12[KOL][h] = L1[i][h];
                        for(int h = N_cols; h < 2 * N_cols; h++)
                            L12[KOL][h] = L2[j][h - N_cols];
                        KOL++;
                    }
                    if(KOL == L) break;
                }
                if(KOL == L) break;
            }


            //L1 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] L1[i];
            }
            delete[] L1;
            //S1 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] S1[i];
            }
            delete[] S1;
            //L2 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] L2[i];
            }
            delete[] L2;
            //S2 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] S2[i];
            }
            delete[] S2;

            std::cout << " L3 L4 S3 S4 making " << std::endl;
            //L3 init
            int** L3 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                L3[i] = new int [N_cols];
            }

            //S3 init
            int** S3 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                S3[i] = new int [H.rows];
            }

            //L4 init
            int** L4 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                L4[i] = new int [N_cols];
            }
            //S4 init
            int** S4 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                S4[i] = new int [H.rows];
            }

            //L3 and L4 creater
            for(int i = 0; i < L; i++)
            for(int j = 0; j < wN; j++)
            {
                std::random_device random_device;
                std::mt19937 generator(random_device());
                std::uniform_int_distribution<> distribution(1, 2);
                L3[i][j] = distribution(generator);
                L4[i][j] = distribution(generator);
            }


            for(int i = 0; i < L; i++)
            for(int j = 0; j < N_cols; j++)
            {
                std::random_device random_device;
                std::mt19937 generator(random_device());
                std::uniform_int_distribution<> distribution(0, N_cols-1);
                int x = distribution(generator);
                int t = L3[i][x];
                L3[i][x] = L3[i][j];
                L3[i][j] = t;
            }

            for(int i = 0; i < L; i++)
            for(int j = 0; j < N_cols; j++)
            {
                std::random_device random_device;
                std::mt19937 generator(random_device());
                std::uniform_int_distribution<> distribution(0, N_cols-1);
                int x = distribution(generator);
                int t = L4[i][x];
                L4[i][x] = L4[i][j];
                L4[i][j] = t;
            }


            

            //S3 creater
            for(int i = 0; i < L; i++)
            for(int j = 0; j < H.rows; j++)
            {
                int sum = 0;
                for(int k = 0; k < N_cols; k++){
                    sum += L3[i][k] * Arr_H[2].elem[j][k];
                }
                S3[i][j] = sum % 3;
            }

            //S4 creater
            for(int i = 0; i < L; i++)
            for(int j = 0; j < H.rows; j++)
            {
                int sum = 0;
                for(int k = 0; k < N_cols; k++){
                    sum += L4[i][k] * Arr_H[3].elem[j][k];
                }
                S4[i][j] = sum % 3;
            }
            std::cout << " L34 S34 making " << std::endl;
            //S34 init
             int** S34 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                S34[i] = new int [H.rows];
            }

            //L34 init
            int** L34 = new int * [L];
            for(int i = 0; i < L; i++)
            {
                L34[i] = new int [2 * N_cols];
            }

            //L34 and S34 creater
            KOL = 0;
            for(int i = 0; i < L; i++)
            {
                for(int j = 0; j < L; j++)
                {
                    int tm = true;
                    for(int k = H.rows / 2; k < H.rows; k++)
                    {
                        if((S3[i][k]+S4[j][k]) % 3 != s.elem[k][0]) tm = false;
                    }
                    if(tm)
                    {
                        for(int h = 0; h < H.rows; h++)
                        {
                            S34[KOL][h] = (S3[i][h] + S4[j][h]) % 3;
                        }
                        for(int h = 0; h < N_cols; h++)
                            L34[KOL][h] = L3[i][h];
                        for(int h = N_cols; h < 2 * N_cols; h++)
                            L34[KOL][h] = L4[j][h - N_cols];
                        KOL++;
                    }
                    if(KOL == L) break;
                }
                if(KOL == L) break;
            }

            //L3 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] L3[i];
            }
            delete[] L3;
            //S3 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] S3[i];
            }
            delete[] S3;
            //L4 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] L4[i];
            }
            delete[] L4;
            //S4 DELETE
            for(int i = 0; i < L; i++)
            {
                delete[] S4[i];
            }
            delete[] S4;

            std::cout << " L1234 making " << std::endl;
            //L1234 init
            int** L1234 = new int * [1];
            for(int i = 0; i < L; i++)
            {
                L1234[i] = new int [4 * N_cols];
            }

            //L1234
            KOL = 0;
            for(int i = 0; i < L; i++)
            {
                for(int j = 0; j < L; j++)
                {
                    int tm = true;
                    for(int k = 0; k < H.rows; k++)
                    {
                        if((S12[i][k]+S34[j][k]) % 3 != s.elem[k][0]) tm = false;
                    }
                    if(tm)
                    {
                        for(int h = 0; h < 2 * N_cols; h++)
                            L1234[KOL][h] = L12[i][h];
                        for(int h = 2 * N_cols; h < 4 * N_cols; h++)
                            L1234[KOL][h] = L34[j][h - 2 * N_cols];
                        KOL = L;
                    }
                    if(KOL == L) break;
                }
                if(KOL == L) break;
            }

            clock_t end = clock();
            std::cout << " END IS " << end << std::endl;
            
            std::cout << " ===== L1234 =====" << std::endl;
            for(int i = 0; i < 1; i++)
            {
                for(int j = 0; j < 4 * N_cols; j++)
                {
                    std::cout << L1234[i][j] << " ";
                }
                std::cout << std::endl;
            }

            

        }catch(std::bad_alloc){
            std::cout << "new crashed" << std::endl;
        }
    }else{
        std::cout << "error input, argc = " << argc << std::endl;
        std::cout << "must be = 3" << std::endl;
    }

}
