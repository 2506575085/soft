#pragma once

#include<bitset>

namespace DES {
//加密函数
//input: 64位输入数据以及密钥
//output: 64位密文
std::bitset<64> encro(std::bitset<64> data_in, std::bitset<64> key_in);

std::bitset<64> decro(std::bitset<64>data_in, std::bitset<64>key_in);

//参数 输入文件名 密钥 输出文件名
int Encry(std::string file_path, std::bitset<64> key, std::string output_path);

//解密算法
int Decry(std::string file_path, std::bitset<64> key, std::string output_path);
}  // namespace DES