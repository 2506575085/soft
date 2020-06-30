#pragma once
#ifndef UNSIGNED_BIGINT_ASM_HPP
#define UNSIGNED_BIGINT_ASM_HPP

#include <intrin.h>
#include "./unsigned_bigint.h"

// 以下函数由汇编语言实现
// 详见unsigned_bigint.asm
extern "C" {
// 计算两个e位大数a+b，结果在ans中
constexpr void __stdcall add_proc(int e, const QWORD* a, const QWORD* b,
                                  QWORD* ans);
// 计算一个e位大数a加上一个64位数b，结果在ans中
constexpr void __stdcall add_mix(int e, const QWORD* a, const QWORD b,
                                 QWORD* ans);
// 计算两个e位大数a-b，结果在ans中
constexpr void __stdcall sub_proc(int e, const QWORD* a, const QWORD* b,
                                  QWORD* ans);
// 计算一个e位大数a减去一个64位数b，结果在ans中
constexpr void __stdcall sub_mix(int e, const QWORD* a, const QWORD b,
                                 QWORD* ans);
// 计算一个e位大数a乘以一个64位数b，结果在ans中
constexpr void __stdcall mul_mix(int e, const QWORD* a, const QWORD b,
                                 QWORD* ans);
// 计算一个e位大数a乘以一个64位数b加上ans，结果在ans中
constexpr void __stdcall mul_mix_add(int e, const QWORD* a, const QWORD b,
                                     QWORD* ans);
// 计算一个e位大数a模一个64位数m，结果在rax（返回值）中
constexpr QWORD __stdcall mod_mix(int e, const QWORD* a, const QWORD m);

constexpr QWORD __stdcall div_128(const QWORD ax, QWORD dx, const QWORD div);

// 计算3个e位大数a+b+ans，结果在ans中
constexpr void __stdcall add_three_this(int e, QWORD* ans, const QWORD* a,
                                        const QWORD* b);

// Intel硬件随机数的辅助函数
void __stdcall real_rand(int e, const QWORD* a);
}
// 以上函数由汇编语言实现

#endif
