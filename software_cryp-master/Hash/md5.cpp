#include "stdafx.h"

#pragma warning(disable : 4996)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "./md5.h"

using namespace std;

#define F(a, b, c) ((a & b) | (~a & c))
#define G(a, b, c) ((a & c) | (b & ~c))
#define H(a, b, c) (a ^ b ^ c)
#define I(a, b, c) (b ^ (a | ~c))
#define ROL(x, n) ((x << n) | (x >> (32 - n)))
#define FF(a, b, c, d, x, s, ac)  \
    {                             \
        a += F(b, c, d) + x + ac; \
        a = ROL(a, s);            \
        a += b;                   \
    }
#define GG(a, b, c, d, x, s, ac)  \
    {                             \
        a += G(b, c, d) + x + ac; \
        a = ROL(a, s);            \
        a += b;                   \
    }
#define HH(a, b, c, d, x, s, ac)  \
    {                             \
        a += H(b, c, d) + x + ac; \
        a = ROL(a, s);            \
        a += b;                   \
    }
#define II(a, b, c, d, x, s, ac)  \
    {                             \
        a += I(b, c, d) + x + ac; \
        a = ROL(a, s);            \
        a += b;                   \
    }

unsigned char padding[] =  // tian chong
    {128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/*
这些参数用于第一轮的运算，以大端字节序来表示，他们分别为：
A=0x01234567，B=0x89ABCDEF，C=0xFEDCBA98，D=0x76543210。
每一个变量给出的数值是高字节存于内存低地址，低字节存于内存高地址，即大端字节序。在程序中变量A、B、C、D的值分别为0x67452301，0xEFCDAB89，0x98BADCFE，0x10325476
*/
void Init(md_5 *text) {
    text->count[0] = 0;
    text->count[1] = 0;
    text->state[0] = 0x67452301;
    text->state[1] = 0xEFCDAB89;
    text->state[2] = 0x98BADCFE;
    text->state[3] = 0x10325476;
}

void encode(unsigned char *output, unsigned int *input, unsigned int len) {
    unsigned int i, j;
    for (i = 0, j = 0; j < len; i += 1) {
        output[j++] = input[i] & 0xFF;         //取后八位
        output[j++] = (input[i] >> 8) & 0xFF;  //右移之后取后八位
        output[j++] = (input[i] >> 16) & 0xFF;
        output[j++] = (input[i] >> 24) & 0xFF;
    }
}

void decode(unsigned int *output, unsigned char *input, unsigned int len) {
    unsigned int i, j;
    for (i = 0, j = 0; j < len; i += 1) {
        output[i] = (input[j++]);
        output[i] |= (input[j++] << 8);
        output[i] |= (input[j++] << 16);
        output[i] |= (input[j++] << 24);
    }
}
/*
第一分组需要将上面四个链接变量复制到另外四个变量中：A到a，B到b，C到c，D到d。从第二分组开始的变量为上一分组的运算结果，即A
= a， B = b， C = c， D = d
主循环有四轮，每轮循环都很相似。第一轮进行16次操作。每次操作对a、b、c和d中的其中三个作一次非线性函数运算，
然后将所得结果加上第四个变量，文本的一个子分组和一个常数。再将所得结果向左环移一个不定的数，并加上a、b、c或d中之一。最后用该结果取代a、b、c或d中之一。
*/
void transform(unsigned int state[4],
               unsigned char block[64])  // md5密码分为64块进行
{
    unsigned int a, b, c, d;
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    unsigned int x[16];

    decode(x, block, 64);
    FF(a, b, c, d, x[0], 7, 0xd76aa478);  // 32位运算
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);

    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x2441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x4881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);

    II(a, b, c, d, x[0], 6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
/*
*用64位来存储填充前信息长度。这64位加在第一步结果的后面，这样信息长度就变为N*512+448+64=(N+1)*512位

*/
void Update(md_5 *text, unsigned char *input, unsigned int length) {
    int i = 0;
    int index = 0;
    unsigned int len = 0;
    index = (text->count[0] >> 3) & 0x3F;  //模64字节的余数,fist time is zero
    len = 64 - index;
    //最前面64位用来存放长度
    text->count[0] += length << 3;  //文本总的位数的低32位
    if (text->count[0] < (length << 3)) text->count[1]++;
    text->count[1] +=
        length >> 29;  //左移三位后求出位数，然后右移32，求出左边32位

    if (length >= len) {
        memcpy(&text->huan_chong[index], input,
               len);  //从第index 位开始用INput复制，长度位len
        transform(text->state, text->huan_chong);
        for (i = len; i + 64 <= length; i += 64)
            transform(text->state, &input[i]);
        index = 0;

    } else
        i = 0;
    memcpy(&text->huan_chong[index], &input[i], length - i);  //最后剩下的一部分
}
void Update_file(md_5 *text, std::string input_filename) {
    int i = 0;
    int index = 0;
    unsigned int len = 0, length;
    std::ifstream file(input_filename, std::ios_base::binary);
    file.seekg(0, std::ios::end);
    length = file.tellg();
    file.seekg(0);

    index = (text->count[0] >> 3) & 0x3F;  //模64字节的余数,fist time is zero
    len = 64 - index;
    //最前面64位用来存放长度
    text->count[0] += length << 3;  //文本总的位数的低32位
    if (text->count[0] < (length << 3)) text->count[1]++;
    text->count[1] +=
        length >> 29;  //左移三位后求出位数，然后右移32，求出左边32位

    if (length >= len) {
        // memcpy(&text->huan_chong[index],input,len);//从第index
        // 位开始用INput复制，长度位len
        file.read((char *)&text->huan_chong[index], len);
        transform(text->state, text->huan_chong);
        for (i = len; i + 64 <= length; i += 64)
            transform(text->state, &text->huan_chong[i % 64]);
        index = 0;

    } else
        i = 0;
    // memcpy(&text->huan_chong[index], &input[i], length-i);//最后剩下的一部分
    file.read((char *)&text->huan_chong[index], length - i);
}
void final_step(md_5 *text, unsigned char result[16]) {
    unsigned int index = 0, padlen = 0;
    unsigned char bits[8];

    index = (text->count[0] >> 3) & 0x3F;  //取后七位，即为模64后的余数
    if (index < 56)                        //需要填充的长度
        padlen = 56 - index;
    else
        padlen = 120 - index;

    encode(bits, text->count, 8);   // count 2位编码位8位Bit
    Update(text, padding, padlen);  //填充
    Update(text, bits, 8);
    encode(result, text->state, 16);
}
std::string fengzhuang(std::string input, md_5 *text) {
    unsigned char enc[64];
    unsigned char re[16];
    std::string hash;
    int length = input.size(), i;
    for (i = 0; i < length; i++) enc[i] = input[i];
    enc[i] = '\0';
    Init(text);
    Update(text, enc, length);
    final_step(text, re);
    std::stringstream ss;
    for (int i = 0; i < 16; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)re[i];
    ss >> hash;
    return hash;
}
// int main(void) {
//    declare();
//    int j;
//    int length;
//
//    unsigned char encrypt[128];
//    cerr << "please input a text:" << endl;
//    cin >> encrypt;
//    unsigned char result[16];
//
//    length = strlen((char *)encrypt);
//    md_5 MD5, MD5_2;
//    for (int i = 0; i < 1000; i++) {
//        Init(&MD5);
//        Update(&MD5, encrypt, length);
//
//        final_step(&MD5, result);
//    }
//    cerr << length << " bytes." << endl;
//
//    printf("加密前:%s\n加密后16位:", encrypt);
//    for (j = 4; j < 12; j++) {
//        printf("%02x", result[j]);
//    }
//
//    printf("\n加密前:%s\n加密后32位:", encrypt);
//    char s[32], s1[32];
//    for (j = 0; j < 16; j++) {
//        printf("%02x", result[j]);
//    }
//    printf("\n");
//    for (j = 0; j < 16; j++) {
//        sprintf(s + 2 * j, "%02x", result[j]);
//    }
//    cerr << s << endl;
//    cerr << "input a file name" << endl;
//    std::string file_name;
//    cin >> file_name;
//    Init(&MD5_2);
//    Update_file(&MD5_2, file_name);
//    final_step(&MD5_2, result);
//    for (j = 0; j < 16; j++) {
//        printf("%02x", result[j]);
//    }
//    return 0;
//}
