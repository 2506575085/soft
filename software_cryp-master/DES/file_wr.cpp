#include "stdafx.h"

#include <stdio.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include "des.h"

namespace DES {
using namespace std;
//参数 输入文件名 密钥 输出文件名
int Encry(std::string file_path, std::bitset<64> key, std::string output_path) {
    std::ifstream file(file_path, std::ios_base::binary | std::ios::in);
    std::ofstream output(output_path, std::ios_base::binary);
    if (!file.is_open()) {
        return 1;
    }
    //给出文件大小
    file.seekg(0, std::ios::end);
    size_t size_of_file = file.tellg();
    file.seekg(0);
    cout << "文件大小是" << size_of_file << endl;
    // temp1用来存储读到的二进制信息
    unsigned long long temp1;
    bitset<64> text;

    while (!file.eof()) {
        file.read((char *)&temp1, sizeof(temp1));
        size_t number = file.gcount();

        if (number != sizeof(temp1)) {
            for (auto i = number; i < 8; i++) {
                *((char *)&temp1 + i) = (char)(8 - number);
            }
        }

        text = bitset<64>(temp1);
        // cout<<"text"<<text<<endl;

        bitset<64> res;
        res = encro(text, key);
        unsigned long long r = res.to_ullong();

        output.write((char *)(&r), sizeof(unsigned long long));
    }
    file.close();
    output.close();
    return 0;
}

//解密算法
int Decry(std::string file_path, std::bitset<64> key, std::string output_path) {
    std::ifstream file(file_path, std::ios_base::binary | std::ios::in);
    std::ofstream output(output_path, std::ios_base::binary);
    if (!file.is_open()) {
        return 1;
    }
    //给出文件大小
    file.seekg(0, std::ios::end);
    size_t size_of_file = file.tellg();
    file.seekg(0);
    cout << "文件大小是" << size_of_file << endl;
    // temp1用来存储读到的二进制信息
    unsigned long long temp1;
    bitset<64> text;
    size_t number = 0;
    //用来记录是否读了64位
    while (!file.eof()) {
        file.read((char *)&temp1, sizeof(temp1));
        number = file.gcount();
        if (number == 0) break;

        text = bitset<64>(temp1);
        // cout<<"text"<<text<<endl;

        // cout<<"本次读取的长度是"<<number<<endl;

        bitset<64> res;
        res = decro(text, key);

        unsigned long long r = res.to_ullong();

        if (size_of_file == file.tellg()) {
            int flag = 1;
            for (int i = 8 - *((char *)(&r) + 7); i < 7; i++) {
                if (*((char *)(&r) + 7) != *((char *)(&r) + i)) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                output.write((char *)(&r), 8 - *((char *)(&r) + 7));
            } else {
                output.write((char *)(&r), sizeof(unsigned long long));
            }

        } else {
            output.write((char *)(&r), sizeof(unsigned long long));
        }
    }
    file.close();
    output.close();
    return 0;
}
}  // namespace DES

// int main(void)
//{
//	bitset<64> key;
//	key =
//bitset<64>("0000111000110010100100100011001011101010011011010000110110000000");
//	Encry("C:\\Users\\skywf\\source\\repos\\file_wr\\file_wr\\data_in.txt",key,"C:\\Users\\skywf\\source\\repos\\file_wr\\file_wr\\data_out.txt");
//
//	Decry("C:\\Users\\skywf\\source\\repos\\file_wr\\file_wr\\data_out.txt",key,"C:\\Users\\skywf\\source\\repos\\file_wr\\file_wr\\jiemi_out.txt");
//	return 1;
//}

// int main()
// {
// 	FILE *fp;
// 	int size = 0;
// 	char *ar;
// 	errno_t err;
// 	//二进制方式打开文件
// 	err = fopen_s(&fp, "testin.txt", "rb");
// 	if (err != 0)
// 	{
// 		printf("Error:Open input.c file fail!\n");
// 		return -1;
// 	}

// 	//求得文件的大小
// 	fseek(fp, 0, SEEK_END);
// 	size = ftell(fp);
// 	std::cout << "size大小是" << size << endl;
// 	rewind(fp);

// 	//读文件
// 	char temp[8] = { 0 };
// 	std::cout << temp << endl;
// 	int count = 0;
// 	while (size > 8)
// 	{
// 		size -= 8;

// 		// for (int i = 0; i < 8; i++)
// 		// {
// 			fread(temp, 1, 8, fp);//每次读一个，共读8次
// 			cout << "temp 是" << temp << endl;
// 		//}

// 	}

// 	if (size > 0)
// 	{
// 		for (int j = 0; j < size; j++)
// 		{
// 			temp[j] = fread(temp, 1, 1, fp);
// 		}
// 		for (int k = size; k < 8; k++)
// 		{
// 			temp[k] = '0';
// 		}
// 	}
// 	cout << "temp是" << temp << endl;

// 	fclose(fp);

// 	return 1;

// }

// int main()
// {
//     ifstream my_file;
//     my_file.open("testin.txt",ios::binary);
//     if(!my_file)
//     {
//         cout<<"没打开"<<endl;
//         return 0;
//     }
//     char a[100];
//     my_file>>a;
// 	cout << a;
//     my_file.close();
//     return 1;
// }

// #include <stdio.h>

// #include <stdlib.h>

// int main()
// {
//     // input binary data
// FILE *fprb;
// if ( fopen_s(&fprb, "testin.txt", "rb") != 0 )  //> fname is path of file by
// const char* type
// {
// 	printf("can't open file\n");
// 	return false;
// }
// char con[50];
// fread(con, sizeof(con), 5, fprb);  //> Con is a container to contain the
// input data cout<<con<<endl; fclose(fprb);

// }
// std::string a1 = "10101010";
// bitset<32> a(a1);
// std::ofstream my_file;
// my_file.open("testout.txt",ios::out);
// my_file<<a1<<endl;
// my_file<<a<<endl;//这进去就是一个32位的数据0000000..10101010
// my_file.close();
// std::ifstream my_file;
// my_file.open("testin.txt",ios::in);
// if(!my_file) return -1;
// char s[40];
// // my_file>>s;

// char array[100];
// ifstream my_file;
// my_file.open("testin.txt",ios::in);
// if(!my_file) return -1;
// while(!my_file.eof())
// {
//     my_file.getline(array,100);//如果一行的数目大于100，这个就会出问题
//     cout<<array<<endl;

// }
// my_file.close();

// std::cout << "Hello World!\n";
// return 1;

// ifstream my_file;
// my_file.open("testin.txt",ios::binary);
