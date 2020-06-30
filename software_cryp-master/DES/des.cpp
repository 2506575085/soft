#include "stdafx.h"

#include<bitset>
#include<iostream>
#include<cstdio>
#include <string>

namespace DES {

using std::bitset;

bitset<64> inial_displace_data(bitset<64> b)
{
	int a[64] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		 60, 52, 44, 36, 28, 20, 12, 4,
		 62, 54, 46, 38, 30, 22, 14, 6,
		 64, 56, 48, 40, 32, 24, 16, 8,
		 57, 49, 41, 33, 25, 17, 9, 1,
		 59, 51, 43, 35, 27, 19, 11, 3,
		 61, 53, 45, 37, 29, 21, 13, 5,
		 63, 55, 47, 39, 31, 23, 15, 7 };
	bitset<64> c;
	for (int i = 0; i < 64; i++)
	{
		c[63-i] = b[a[i]-1];
	}
	return c;
}

bitset<56> inial_displace_key(bitset<64> b)
{
	bitset<64> temp;

	for (int j = 0; j < 64; j++)
	{	
		temp[j] = b[63 - j];
		
	}
	int a[56] =
	{
		57, 49, 41, 33, 25, 17, 9, 1,
		 58, 50, 42, 34, 26, 18, 10, 2,
		 59, 51, 43, 35, 27, 19, 11, 3,
		 60, 52, 44, 36, 63, 55, 47, 39,
		 31, 23, 15, 7, 62, 54, 46, 38,
		 30, 22, 14, 6, 61, 53, 45, 37,
		 29, 21, 13, 5, 28, 20, 12, 4
	};
	bitset<56> c;
	for (int i = 0; i < 56; i++)
	{
		c[i] = temp[a[i]-1];
	}
	return c;

}
/*
#num_shift = [1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1]16次移位
#有效密钥移位(没问题)
#input:56位密钥,移位次数
#output:子密钥
*/
bitset<56> shift_key(bitset<56> key_56, int shift_num)
{
	// bitset<56> temp_r;
	// int q;
	// for ( q = 0; q < 56; q++)
	// {
	// 	temp_r[q] = key_56[55 - q];
	// }
	// for (q = 0; q < 56; q++)
	// {
	// 	 key_56[q] = temp_r[q];
	// }
	//上面那个做了个倒序
	if (shift_num >= 28)
	{
		shift_num -= 28;
	}
	bitset<28>temp1;
	bitset<28>temp2;
	int i;
	for (i = 0; i < 28; i++)
	{
		temp1[i] = key_56[i];
		temp2[i] = key_56[28+i];
	}
	for (i = 0; i < shift_num; i++)
	{
		if (temp1[0] == 1)
		{
			temp1 >>= 1;
			temp1[27] = 1;
		}
        else if(temp1[0] ==0)
		{
            temp1 >>= 1;
        }    
		if (temp2[0] == 1)
		{
			temp2 >>= 1;
			temp2[27] = 1;
		}
		else if(temp2[0] ==0){
            temp2 >>= 1;
        }
	}
	bitset<56> c;
	for (i = 0; i < 28; i++)
	{
		c[i] = temp1[i];
		c[28 + i] = temp2[i];
	}
	return c;
}

/*
#对子密钥进行压缩得到48位的(没有问题)
#input: 56位密钥
#output: 48位密钥
*/
bitset<48> compress_key(bitset<56> key_56)
{
	int a[48] = { 14, 17, 11, 24, 1, 5,
		 3, 28, 15, 6, 21, 10,
		 23, 19, 12, 4, 26, 8,
		 16, 7, 27, 20, 13, 2,
		 41, 52, 31, 37, 47, 55,
		 30, 40, 51, 45, 33, 48,
		 44, 49, 39, 56, 34, 53,
		 46, 42, 50, 36, 29, 32 };
	bitset<48> c;
	for (int i = 0; i < 48; i++)
	{
		c[i] = key_56[a[i]-1];
	}
	return c;
}
/*
#对数据的L0不变，L1扩展为48位以后做异或
#input: key_48,data_64
#output: encro_48 已经加密的48位数据
*/

bitset<48> xorkey_data(bitset<64> data_64, bitset<48> key_48)
{
	int a[48] = {
		32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1 };
	bitset<64> R_32;
	int i;
	// for (i = 0; i < 32; i++)
	 // {
	// 	R_32[i] = data_64[32 + i];
	// }
	R_32 = data_64 << 32;
	bitset<48> R_48;
	for (i = 0; i < 48; i++)
	{
		R_48[i] = R_32[a[i]-1];
		R_48[i] = R_48[i] ^ key_48[i];
	}

	return R_48;

}

bitset<4> int_to4bin(int k)
{
    return bitset<4>(k);
}

bitset<32> new_32(bitset<48> encry_data_48)
{
    int s1[64] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13, };
    int s2[64] = {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9, };
    int s3[64] = {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12, };
    int s4[64] = {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14, };
    int s5[64] = {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3, };
    int s6[64] = {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13, };
    int s7[64] = {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12, };
    int s8[64] = {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11, };
    int i=0;
    int j=0;
    int count=0;
    bitset<32> res;
    bitset<6> temp1;
    int temp_num;
    bitset<4> temp2;      //存放最后给出的四位二进制数字
    bitset<2> row_first;
    bitset<4> rol_first;
    unsigned long row;
    unsigned long rol;
    for (count=0;count<8;count++)
    {
        for (i=0;i<6;i++)
        {
            temp1[5-i] = encry_data_48[count*6+i];
        }
        row_first[0] = temp1[0];
        row_first[1] = temp1[5];
        for(int p=0;p<4;p++)
        {
            rol_first[p] = temp1[p+1];
        }
		//这个地方的高位和低位和我最开始想的是反的，所以直接改前面吧
        row = row_first.to_ulong();
        rol = rol_first.to_ulong();
        switch (count)
        {
        case 0:
            temp_num = s1[row*16+rol];
            
            break;
        case 1:
            temp_num = s2[row*16+rol];

            break;
        case 2:
            temp_num = s3[row*16+rol];

            break;
            case 3:
            temp_num = s4[row*16+rol];

            break;
            case 4:
            temp_num = s5[row*16+rol];

            break;
            case 5:
            temp_num = s6[row*16+rol];

            break;
            case 6:
            temp_num = s7[row*16+rol];

            break;
            case 7:
            temp_num = s8[row*16+rol];

            break;
        
        }
        temp2 = int_to4bin(temp_num);
        for(i=0;i<4;i++)
        {
			//std::cout << "temp2["<<i<<"] ="<<temp2[i];
            res[i+count*4] = temp2[3-i];
        }
		//std::cout << "\n";
    }
    return res;
}

bitset<32> p_box(bitset<32> data_32)
{
    int a[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
    bitset<32> c;
    for (int i =0;i<32;i++)
    {
        c[i] = data_32[a[i]-1];
    }
    return c;

}

bitset<64> final_dis(bitset<64> data_64)
{
    int a[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
    bitset<64> c;
    for (int i =0;i<64;i++)
    {
        c[i] = data_64[a[i]-1];
    }
    return c;

}
//加密函数
//input: 64位输入数据以及密钥
//output: 64位密文
bitset<64> encro(bitset<64> data_in,bitset<64> key_in)
{
    bitset<64>data_turn;
    bitset<56>key_turn;
    bitset<48>key_48;
    bitset<48>encro_48;
    bitset<32>R0;
    bitset<32>RR0;
    bitset<64>temp;
    bitset<32> L32;
    bitset<32> R32;
    bitset<64> res_cro; //输出的密文
    data_turn = inial_displace_data(data_in);
    key_turn = inial_displace_key(key_in);
    int num_shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    for (int i=0;i<16;i++)
    {
        key_turn = shift_key(key_turn,num_shift[i]);
        key_48 = compress_key(key_turn);
        encro_48 = xorkey_data(data_turn,key_48);
        R0 = new_32(encro_48);
        RR0 = p_box(R0);
        temp = data_turn;
        for(int p=0;p<32;p++)
        {
            data_turn[p]=data_turn[p+32];
        }
        for (int j=0;j<32;j++)
        {
            data_turn[j+32] = (temp[j]^RR0[j]);
        }
        if(i==15)
        {
            for(int k=0;k<32;k++)
            {
                L32[k]=data_turn[k];
                data_turn[k]=data_turn[32+k];
                data_turn[32+k]=L32[k];
            }

        }
    }

    res_cro = final_dis(data_turn);
    bitset<64> temp_d;
	int q;
	for ( q = 0; q < 64; q++)
	{
		temp_d[q] = res_cro[63 - q];
	}
	for (q = 0; q < 64; q++)
	{
		res_cro[q] = temp_d[q] ;
	}
   // printf("加密以后的密文是:\n");
   // std::cout<<res_cro<<"\n";
    return res_cro;
}

bitset<64> decro(bitset<64>data_in, bitset<64>key_in)
{
	bitset<64>data_turn;
	bitset<56>key_turn;
	bitset<56>key_this; //每一次的key
	bitset<48>key_48;
	bitset<48>encro_48;
	bitset<32>R0;
	bitset<32>RR0;
	bitset<64>temp;
	bitset<32> L32;
	bitset<32> R32;
	bitset<64> res_cro; //输出的密文
	// bitset<64> temp_in;
	// int ss;
	// for ( ss = 0; ss < 64; ss++)
	// {
	// 	temp_in[ss] = data_in[63 - ss];
	// }
	// for (ss = 0; ss < 64; ss++)
	// {
	// 	data_in[ss] = temp_in[ss] ;
	// }
	data_turn = inial_displace_data(data_in);
	key_turn = inial_displace_key(key_in);
	int num_rev_shift[16] = { 28, 27, 25, 23, 21, 19, 17, 15, 14, 12, 10, 8, 6, 4, 2, 1 };


	for (int i = 0; i < 16; i++)
	{
		key_this = shift_key(key_turn, num_rev_shift[i]);
		key_48 = compress_key(key_this);
		encro_48 = xorkey_data(data_turn, key_48);
		R0 = new_32(encro_48);
		RR0 = p_box(R0);
		temp = data_turn;
		for (int p = 0; p < 32; p++)
		{
			data_turn[p] = data_turn[p + 32];
		}
		for (int j = 0; j < 32; j++)
		{
			data_turn[j + 32] = (temp[j] ^ RR0[j]);
		}
		if (i == 15)
		{
			for (int k = 0; k < 32; k++)
			{
				L32[k] = data_turn[k];
				data_turn[k] = data_turn[32 + k];
				data_turn[32 + k] = L32[k];
			}

		}
	}
	res_cro = final_dis(data_turn);

	bitset<64> temp_d;
	int q;
	for (q = 0; q < 64; q++)
	{
		temp_d[q] = res_cro[63 - q];
	}
	for (q = 0; q < 64; q++)
	{
		res_cro[q] = temp_d[q];
	}

	//printf("解密以后的明文是:\n");
	//std::cout<<res_cro<<"\n";
	return res_cro;
}
}  // namespace DES
