﻿#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// AES-128加密接口，输入key应为16字节长度，输入长度应该是16字节整倍数，
// 这样输出长度与输入长度相同，函数调用外部为输出数据分配内存
//keylen为初始秘钥的长度，len为输入的待加密数据的长度，必须为输入长度应该是16字节整倍数，
int aesEncrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *pt, uint8_t *ct, uint32_t len);

// AES128解密， 参数要求同加密
int aesDecrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *ct, uint8_t *pt, uint32_t len);

void aesEncryptFile(const uint8_t *key, uint32_t keyLen, const char *in_path, const char *out_path);

void aesDecryptFile(const uint8_t *key, uint32_t keyLen, const char *in_path, const char *out_path);

#ifdef __cplusplus
}
#endif
