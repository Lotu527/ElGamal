#ifndef MD5_H
#define MD5_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define ROTL32(dword, n) ((dword) << (n) ^ ((dword) >> (32 - (n))))
/*MD5的结果数据长度*/
static const unsigned int MD5_HASH_SIZE   = 16;

/*每次处理的BLOCK的大小*/
static const unsigned int MD5_BLOCK_SIZE = 64;
//================================================================================================
/*MD5的算法*/


/*md5算法的上下文，保存一些状态，中间数据，结果*/
struct md5_ctx
{
    /*处理的数据的长度*/
    unsigned long length;
    /*还没有处理的数据长度*/
    unsigned long unprocessed;
    /*取得的HASH结果（中间数据）*/
    unsigned int  hash[4];
};




static void md5_init(md5_ctx *ctx)
{
    ctx->length = 0;
    ctx->unprocessed = 0;

    /* initialize state */
    /*不要奇怪为什么初始数值与参考数值不同,这是因为我们使用的数据结构的关系,大的在低位，小的在高位,8位8位一读*/
    ctx->hash[0] = 0x67452301; /*应该这样读0x01234567*/
    ctx->hash[1] = 0xefcdab89; /*0x89abcdef*/
    ctx->hash[2] = 0x98badcfe; /*0xfedcba98*/
    ctx->hash[3] = 0x10325476; /*0x76543210*/
}

#define MD5_F(x, y, z) ((((y) ^ (z)) & (x)) ^ (z))
#define MD5_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define MD5_H(x, y, z) ((x) ^ (y) ^ (z))
#define MD5_I(x, y, z) ((y) ^ ((x) | (~z)))

/* 一共4轮，每一轮使用不同函数*/
#define MD5_ROUND1(a, b, c, d, x, s, ac) {        \
        (a) += MD5_F((b), (c), (d)) + (x) + (ac); \
        (a) = ROTL32((a), (s));                   \
        (a) += (b);                               \
    }
#define MD5_ROUND2(a, b, c, d, x, s, ac) {        \
        (a) += MD5_G((b), (c), (d)) + (x) + (ac); \
        (a) = ROTL32((a), (s));                   \
        (a) += (b);                               \
    }
#define MD5_ROUND3(a, b, c, d, x, s, ac) {        \
        (a) += MD5_H((b), (c), (d)) + (x) + (ac); \
        (a) = ROTL32((a), (s));                   \
        (a) += (b);                               \
    }
#define MD5_ROUND4(a, b, c, d, x, s, ac) {        \
        (a) += MD5_I((b), (c), (d)) + (x) + (ac); \
        (a) = ROTL32((a), (s));                   \
        (a) += (b);                               \
    }


static void md5_process_block(unsigned int state[4], const unsigned int block[MD5_BLOCK_SIZE / 4])
{
    register unsigned a, b, c, d;
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];

    const unsigned int *x = block;


    MD5_ROUND1(a, b, c, d, x[ 0],  7, 0xd76aa478);
    MD5_ROUND1(d, a, b, c, x[ 1], 12, 0xe8c7b756);
    MD5_ROUND1(c, d, a, b, x[ 2], 17, 0x242070db);
    MD5_ROUND1(b, c, d, a, x[ 3], 22, 0xc1bdceee);
    MD5_ROUND1(a, b, c, d, x[ 4],  7, 0xf57c0faf);
    MD5_ROUND1(d, a, b, c, x[ 5], 12, 0x4787c62a);
    MD5_ROUND1(c, d, a, b, x[ 6], 17, 0xa8304613);
    MD5_ROUND1(b, c, d, a, x[ 7], 22, 0xfd469501);
    MD5_ROUND1(a, b, c, d, x[ 8],  7, 0x698098d8);
    MD5_ROUND1(d, a, b, c, x[ 9], 12, 0x8b44f7af);
    MD5_ROUND1(c, d, a, b, x[10], 17, 0xffff5bb1);
    MD5_ROUND1(b, c, d, a, x[11], 22, 0x895cd7be);
    MD5_ROUND1(a, b, c, d, x[12],  7, 0x6b901122);
    MD5_ROUND1(d, a, b, c, x[13], 12, 0xfd987193);
    MD5_ROUND1(c, d, a, b, x[14], 17, 0xa679438e);
    MD5_ROUND1(b, c, d, a, x[15], 22, 0x49b40821);

    MD5_ROUND2(a, b, c, d, x[ 1],  5, 0xf61e2562);
    MD5_ROUND2(d, a, b, c, x[ 6],  9, 0xc040b340);
    MD5_ROUND2(c, d, a, b, x[11], 14, 0x265e5a51);
    MD5_ROUND2(b, c, d, a, x[ 0], 20, 0xe9b6c7aa);
    MD5_ROUND2(a, b, c, d, x[ 5],  5, 0xd62f105d);
    MD5_ROUND2(d, a, b, c, x[10],  9,  0x2441453);
    MD5_ROUND2(c, d, a, b, x[15], 14, 0xd8a1e681);
    MD5_ROUND2(b, c, d, a, x[ 4], 20, 0xe7d3fbc8);
    MD5_ROUND2(a, b, c, d, x[ 9],  5, 0x21e1cde6);
    MD5_ROUND2(d, a, b, c, x[14],  9, 0xc33707d6);
    MD5_ROUND2(c, d, a, b, x[ 3], 14, 0xf4d50d87);
    MD5_ROUND2(b, c, d, a, x[ 8], 20, 0x455a14ed);
    MD5_ROUND2(a, b, c, d, x[13],  5, 0xa9e3e905);
    MD5_ROUND2(d, a, b, c, x[ 2],  9, 0xfcefa3f8);
    MD5_ROUND2(c, d, a, b, x[ 7], 14, 0x676f02d9);
    MD5_ROUND2(b, c, d, a, x[12], 20, 0x8d2a4c8a);

    MD5_ROUND3(a, b, c, d, x[ 5],  4, 0xfffa3942);
    MD5_ROUND3(d, a, b, c, x[ 8], 11, 0x8771f681);
    MD5_ROUND3(c, d, a, b, x[11], 16, 0x6d9d6122);
    MD5_ROUND3(b, c, d, a, x[14], 23, 0xfde5380c);
    MD5_ROUND3(a, b, c, d, x[ 1],  4, 0xa4beea44);
    MD5_ROUND3(d, a, b, c, x[ 4], 11, 0x4bdecfa9);
    MD5_ROUND3(c, d, a, b, x[ 7], 16, 0xf6bb4b60);
    MD5_ROUND3(b, c, d, a, x[10], 23, 0xbebfbc70);
    MD5_ROUND3(a, b, c, d, x[13],  4, 0x289b7ec6);
    MD5_ROUND3(d, a, b, c, x[ 0], 11, 0xeaa127fa);
    MD5_ROUND3(c, d, a, b, x[ 3], 16, 0xd4ef3085);
    MD5_ROUND3(b, c, d, a, x[ 6], 23,  0x4881d05);
    MD5_ROUND3(a, b, c, d, x[ 9],  4, 0xd9d4d039);
    MD5_ROUND3(d, a, b, c, x[12], 11, 0xe6db99e5);
    MD5_ROUND3(c, d, a, b, x[15], 16, 0x1fa27cf8);
    MD5_ROUND3(b, c, d, a, x[ 2], 23, 0xc4ac5665);

    MD5_ROUND4(a, b, c, d, x[ 0],  6, 0xf4292244);
    MD5_ROUND4(d, a, b, c, x[ 7], 10, 0x432aff97);
    MD5_ROUND4(c, d, a, b, x[14], 15, 0xab9423a7);
    MD5_ROUND4(b, c, d, a, x[ 5], 21, 0xfc93a039);
    MD5_ROUND4(a, b, c, d, x[12],  6, 0x655b59c3);
    MD5_ROUND4(d, a, b, c, x[ 3], 10, 0x8f0ccc92);
    MD5_ROUND4(c, d, a, b, x[10], 15, 0xffeff47d);
    MD5_ROUND4(b, c, d, a, x[ 1], 21, 0x85845dd1);
    MD5_ROUND4(a, b, c, d, x[ 8],  6, 0x6fa87e4f);
    MD5_ROUND4(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    MD5_ROUND4(c, d, a, b, x[ 6], 15, 0xa3014314);
    MD5_ROUND4(b, c, d, a, x[13], 21, 0x4e0811a1);
    MD5_ROUND4(a, b, c, d, x[ 4],  6, 0xf7537e82);
    MD5_ROUND4(d, a, b, c, x[11], 10, 0xbd3af235);
    MD5_ROUND4(c, d, a, b, x[ 2], 15, 0x2ad7d2bb);
    MD5_ROUND4(b, c, d, a, x[ 9], 21, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}


static void md5_update(md5_ctx *ctx, const unsigned char *buf, unsigned int size)
{
    /*为什么不是=，因为在某些环境下，可以多次调用zen_md5_update，
     * 但这种情况，必须保证前面的调用，每次都没有unprocessed*/
    ctx->length += size;

    /*每个处理的块都是64字节*/
    while (size >= MD5_BLOCK_SIZE)
    {
        md5_process_block(ctx->hash, reinterpret_cast<const unsigned int *>(buf));
        buf  += MD5_BLOCK_SIZE;    /*buf指针每一次向后挪动64*/
        size -= MD5_BLOCK_SIZE;   /*每一次处理64个字符*/
    }

    ctx->unprocessed = size;   /*未处理的字符数数目记录下来*/
}



static void md5_final(md5_ctx *ctx, const unsigned char *buf, unsigned int size, unsigned char *result)
{
    unsigned int message[MD5_BLOCK_SIZE / 4];
    memset(message, 0 ,(MD5_BLOCK_SIZE/4) * sizeof(unsigned int));
    /*保存剩余的数据，我们要拼出最后1个（或者两个）要处理的块，前面的算法保证了，最后一个块肯定小于64个字节*/
    if (ctx->unprocessed)
    {
        memcpy(message, buf + size - ctx->unprocessed, static_cast<unsigned int>( ctx->unprocessed));
       /*================================================================================
        这里的memcpy复制很有趣,是按照字节复制比如说buf --- 0x11 0x14 0xab 0x23 0xcd  |
        ctx>unprocessed_=5 现在copy至 message --- 0x23ab1411 0x000000cd
        这样的话,下面的也很好解释了!
       =================================================================================*/
    }
      /*=================================================================================
       用法：static_cast < type-id > ( expression )
       该运算符把expression转换为type-id类型
       ==================================================================================*/

    /*得到0x80要添加在的位置（在unsigned int 数组中）*/
    unsigned int index = ((unsigned int)ctx->length & 63) >> 2;
    /*一次性处理64个unsigned int型数据,(unsigned int)ctx->length_ & 63求出余下多少未处理的字符*/

    unsigned int shift = ((unsigned int)ctx->length & 3) * 8;
    /*一个message里面可以放置4个字符数据,找到应该移动的位数*/

    /*添加0x80进去，并且把余下的空间补充0*/
    message[index++] ^= 0x80 << shift;   /*^ 位异或*/

    /*如果这个block还无法处理，其后面的长度无法容纳长度64bit，那么先处理这个block*/
    if (index > 14)
    {
        while (index < 16)
        {
            message[index++] = 0;
        }

        md5_process_block(ctx->hash, message);
        index = 0;
    }

    /*补0*/
    while (index < 14)
    {
        message[index++] = 0;
    }

    /*保存长度，注意是bit位的长度*/
    unsigned long data_len = (ctx->length) << 3;

    message[14] = (unsigned int) (data_len & 0x00000000FFFFFFFF);
    message[15] = (unsigned int) ((data_len & 0xFFFFFFFF00000000ULL) >> 32);

    md5_process_block(ctx->hash, message);
    memcpy(result, &ctx->hash, MD5_HASH_SIZE);
}


 unsigned char* md5(const unsigned char *buf,  unsigned int  size,   unsigned char result[MD5_HASH_SIZE])
{
    md5_ctx ctx;
    md5_init(&ctx);   /*初始化*/
    md5_update(&ctx, buf, size);
    md5_final(&ctx, buf, size, result);
    return result;
}



#endif // MD5_H
