#include "stdafx.h"

#pragma warning(disable : 4996)

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "./sha256.h"

#define maxlen 1000000
using namespace std;
typedef unsigned int uint;
typedef unsigned char ubyte;
typedef unsigned long long ull;

#define SHA256_ROTL(a, b) \
    (((a >> (32 - b)) & (0x7fffffff >> (31 - b))) | (a << b))
#define SHA256_SR(a, b) ((a >> b) & (0x7fffffff >> (b - 1)))
#define SHA256_Ch(x, y, z) ((x & y) ^ ((~x) & z))
#define SHA256_Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_E0(x) \
    (SHA256_ROTL(x, 30) ^ SHA256_ROTL(x, 19) ^ SHA256_ROTL(x, 10))
#define SHA256_E1(x) \
    (SHA256_ROTL(x, 26) ^ SHA256_ROTL(x, 21) ^ SHA256_ROTL(x, 7))
#define SHA256_O0(x) (SHA256_ROTL(x, 25) ^ SHA256_ROTL(x, 14) ^ SHA256_SR(x, 3))
#define SHA256_O1(x) \
    (SHA256_ROTL(x, 15) ^ SHA256_ROTL(x, 13) ^ SHA256_SR(x, 10))

char instr[maxlen];

const uint k[] = {  // hash initial number
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

inline uint rrot(uint val, int pos) {  // xun huan you yi
    pos %= 32;
    return (val >> pos) | (val << (32 - pos));
}

void sha_256(char *digest, const char *str) {
    uint orilen = strlen(str);  // record the length of the string
    uint chunks_count;          // the number of chunks
    if (!(orilen + 9) % 64)
        chunks_count = (orilen + 9) / 64;
    else
        chunks_count = (orilen + 9) / 64 + 1;
    ull total_count = orilen * 8;
    uint *filldata = new uint[chunks_count * 16];  // tian chong shu ju
    memset(filldata, 0, sizeof(uint) * chunks_count * 16);

    ubyte *pdata = (ubyte *)filldata;
    uint idx;
    for (idx = 0; idx < orilen; ++idx)  // 3,2,1,0,7,6,5,4,11,10,9,8 ... ...
    {
        if (idx % 4 == 0)
            pdata[idx + 3] = str[idx];
        else if (idx % 4 == 1)
            pdata[idx + 1] = str[idx];
        else if (idx % 4 == 2)
            pdata[idx - 1] = str[idx];
        else if (idx % 4 == 3)
            pdata[idx - 3] = str[idx];
    }
    pdata[idx + 3 - 2 * (idx % 4)] =
        0x80;  // append length of message (before pre-processing), in bits, as
               // 64-bit big-endian integer
    ++idx;

    ubyte *pbyte = (ubyte *)&total_count;
    for (uint i = 0, j = 64 * chunks_count - 4; i < 8; ++i) {
        if (i == 4) j -= 8;
        pdata[j + i] = pbyte[i];
    }
    // eight initial numbers
    uint H[8], a, b, c, d, e, f, g, h, w[80], s[2];
    H[0] = 0x6a09e667;
    H[1] = 0xbb67ae85;
    H[2] = 0x3c6ef372;
    H[3] = 0xa54ff53a;
    H[4] = 0x510e527f;
    H[5] = 0x9b05688c;
    H[6] = 0x1f83d9ab;
    H[7] = 0x5be0cd19;

    for (uint i = 0; i < chunks_count * 16; i += 16) {
        uint *puint = &filldata[i];
        printf("chunk: %d\n", i / 16);
        for (uint j = 0; j < 16; ++j) {
            w[j] = puint[j];
            printf("%08X ", w[j]);
            if ((j + 1) % 4 == 0) printf("\n");
        }
        /*
         * 对于每一块，将块分解为16个32-bit的big-endian的字，记为w[0], …, w[15]
         * 也就是说，前16个字直接由消息的第i个块分解得到
         * 其余的字由迭代公式得到
         */

        for (uint j = 16; j < 64; ++j)  // die dai gong shi
        {
            s[0] =
                (rrot(w[j - 15], 7)) ^ (rrot(w[j - 15], 18)) ^ (w[j - 15] >> 3);
            s[1] =
                (rrot(w[j - 2], 17)) ^ (rrot(w[j - 2], 19)) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s[0] + w[j - 7] + s[1];
        }
        a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6],
        h = H[7];
        /*
         * 映射 $ Map(H_{i-1}) = H_{i} $ 包含了64次加密循环
         * 即进行64次加密循环即可完成一次迭代
         */
        for (uint j = 0; j < 64;
             ++j) {  // T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + K[i] +
                     // W[i];//T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
            uint maj, t[3], ch;
            s[0] = (rrot(a, 2)) ^ (rrot(a, 13)) ^
                   (rrot(a, 22));               // sigma_0 operate
            maj = (a & b) ^ (a & c) ^ (b & c);  // maj operate
            t[2] = s[0] + maj;
            s[1] = rrot(e, 6) ^ rrot(e, 11) ^ rrot(e, 25);  // sigma_1 operate
            ch = (e & f) ^ ((~e) & g);                      // ch operate
            t[1] = h + s[1] + ch + k[j] + w[j];

            //            t[1] = h + SHA256_E1(e) + SHA256_Ch(e, f, g) + k[i] +
            //            w[i];
            //           t[2] = SHA256_E0(a) + SHA256_Maj(a, b, c);

            h = g, g = f, f = e, e = d + t[1], d = c, c = b, b = a,
            a = t[1] + t[2];
            printf(
                "%2d: a=%08x b=%08x c=%08x d=%08x\n    e=%08x f=%08x g=%08x "
                "h=%08x\n",
                j, a, b, c, d, e, f, g, h);
        }
        H[0] += a, H[1] += b, H[2] += c, H[3] += d, H[4] += e, H[5] += f,
            H[6] += g, H[7] += h;
    }
    for (int i = 0; i < 8; ++i) {
        sprintf(digest + i * 8, "%08x", H[i]);
    }
    delete[] filldata;
}
extern char *FileSHA256(const char *file, char *sha256) {
    /*
    计算文件SHA-256
    参数说明：
    file        文件路径字符串指针
    sha256         用于保存SHA-256的字符串指针
    返回值为参数sha256
    */
    FILE *fh;
    char *addlp, T[64];
    long addlsize, j, W[64], T1, T2, A, B, C, D, E, F, G, H, H0, H1, H2, H3, H4,
        H5, H6, H7;
    long long length, i, cpys;
    void *pp, *ppend;
    H0 = 0x6a09e667, H1 = 0xbb67ae85, H2 = 0x3c6ef372, H3 = 0xa54ff53a;
    H4 = 0x510e527f, H5 = 0x9b05688c, H6 = 0x1f83d9ab, H7 = 0x5be0cd19;
    fh = fopen(file, "rb");
    fseek(fh, 0, SEEK_END);
    length = _ftelli64(fh);
    addlsize = (56 - length % 64 > 0) ? (64) : (128);
    if (!(addlp = (char *)malloc(addlsize))) return 0;
    cpys = ((length - (56 - length % 64)) > 0) ? (length - length % 64) : (0);
    j = (long)(length - cpys);
    if (!(pp = (char *)malloc(j))) return 0;
    fseek(fh, -j, SEEK_END);
    fread(pp, 1, j, fh);
    for (i = 0; i < j; addlp[i + 3 - 2 * (i % 4)] = ((char *)pp)[i], i++)
        ;
    free(pp);
    for (addlp[i + 3 - 2 * (i % 4)] = 128, i++; i < addlsize;
         addlp[i + 3 - 2 * (i % 4)] = 0, i++)
        ;
    *((long *)(addlp + addlsize - 4)) = length << 3;
    *((long *)(addlp + addlsize - 8)) = length >> 29;
    for (rewind(fh); 64 == fread(W, 1, 64, fh);) {
        for (i = 0; i < 64; T[i + 3 - 2 * (i % 4)] = ((char *)W)[i], i++)
            ;
        for (i = 0; i < 16; W[i] = ((long *)T)[i], i++)
            ;
        for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] +
                                     SHA256_O0(W[i - 15]) + W[i - 16]),
            i++)
            ;
        A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
        for (i = 0; i < 64; i++) {
            T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + k[i] + W[i];
            T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
            H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
        }
        H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
    }
    for (pp = addlp, ppend = addlp + addlsize; pp < ppend;
         pp = (long *)pp + 16) {
        for (i = 0; i < 16; W[i] = ((long *)pp)[i], i++)
            ;
        for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] +
                                     SHA256_O0(W[i - 15]) + W[i - 16]),
            i++)
            ;
        A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
        for (i = 0; i < 64; i++) {
            T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + k[i] + W[i];
            T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
            H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
        }
        H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
    }
    free(addlp);
    fclose(fh);
    sprintf(sha256, "%08X%08X%08X%08X%08X%08X%08X%08X", H0, H1, H2, H3, H4, H5,
            H6, H7);
    return sha256;
}
// int main() {
//    declare();
//    cerr << "please input choice : " << endl;
//    cerr << "----------1.file-----" << endl;
//    cerr << "----------2.text-----" << endl;
//    int choice;
//    cin >> choice;
//    if (choice == 2) {
//        char text[256];
//        cerr << "please input a text" << endl;
//        cin >> text;
//        char sha256[65];
//        sha_256(sha256, text);
//        puts(sha256);
//        printf(
//            "__________________________________________________________________"
//            "______________\n");
//    } else if (choice == 1) {
//        char name[100];
//        cerr << "please input the name of the file" << endl;
//        cin >> name;
//        char sha256[256];
//        FileSHA256(name, sha256);
//        puts(sha256);
//    }
//    return 0;
//}
