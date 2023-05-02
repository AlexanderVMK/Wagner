#include <iostream>
#include <fstream>
#include <random>

template <typename T>
void swap(T *a, T *b)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}


int main(int argc, char * argv[]){
	std::ofstream out_H, out_s;
	std::string H,s;
	H = argv[1];
	H = H + "_H.txt";
	out_H.open(H);
	s = argv[1];
	s = s + "_s.txt";
	out_s.open(s);
	int rows, cols, w;
	std::cin >> rows >> cols >> w;


	int * * elem_H;
	elem_H = new int *[rows];
    for(int i = 0; i < rows; i++)
    {
        elem_H[i] = new int [cols];
        for(int j = 0; j < cols; j++)
        {
			std::random_device random_device;
        	std::mt19937 generator(random_device());
        	std::uniform_int_distribution<> distribution(0, 2);
        	int x = distribution(generator);
            elem_H[i][j] = x;
        }
    }
	out_H << rows << " " << cols << "\n";
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			out_H << elem_H[i][j];
			if (j != cols - 1) out_H << " ";
		}
		if (i != rows - 1) out_H << "\n";
	}

	int * elem_e;
	elem_e = new int [cols];
	for(int i = 0; i < w; i++)
	{
		std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(1, 2);
		elem_e[i] = distribution(generator);
	}
	for(int i = w; i < cols; i++)
		elem_e[i] = 0;
	for(int i = 0; i < cols; i++)
    {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, cols-1);
        int x = distribution(generator);
        swap(&elem_e[i], &elem_e[(x)]);
    }
	out_s << rows << " " << 1 << "\n";

	int * elem_s;
	elem_s = new int [rows];
	for(int i = 0; i < rows; i++)
    {
        int tmp = 0;
        for(int k = 0; k < cols; k++)
        {
            tmp += elem_H[i][k] * elem_e[k];
        }
        elem_s[i]= tmp % 3;
    }
	for(int i = 0; i < rows; i++)
	{
		out_s << elem_s[i];
		if(i != rows) out_s << " ";
	}
}
