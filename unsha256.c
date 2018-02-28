/*********************************************************************
* Filename:   sha256.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Performs known-answer tests on the corresponding SHA1
              implementation. These tests do not encompass the full
              range of available test vectors, however, if the tests
              pass it is very, very likely that the code is correct
              and was compiled properly. This code also serves as
              example usage of the functions.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>
//#include "sha256.h"

//d39a2165  4d24d6c   b85e2ce9  b6ae8fff  fb121210  948d25b6  961f4894  b21bad3d  |  c67178f2  |  12b1edeb  
//ba7816bf  8f01cfea  414140de  5dae2223  b00361a3  96177a9c  b410ff61  f20015ad  

#include <stdio.h>
#define _d(x)           do{ fprintf(stderr, "%s %x\n", #x, (unsigned)x); fflush(stderr); } while(0)
#define _dw(x)          do{ fprintf(stderr, "%x ", (unsigned)x); fflush(stderr); } while(0)
#define _endl           do{ fprintf(stderr, "\n"); fflush(stderr); } while(0)
#define _prn(x)         do{ fprintf(stderr, "%s", x); fflush(stderr); } while(0)

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

int main(){

//    uint32_t A = 0xd39a2165;
//    uint32_t B = 0x4d24d6c;
//    uint32_t sum = 0xd86c6ed1;
//_d(sum-A);
//_d(sum-B);
//_d(sum+A);
//_d(sum+B);

    int i;

    uint32_t h[8] = { 0xd39a2165,  0x4d24d6c,   0xb85e2ce9,  0xb6ae8fff,  
                      0xfb121210,  0x948d25b6,  0x961f4894,  0xb21bad3d };
    uint32_t hprime[8];
    uint32_t k = 0xbef9a3f7;
    uint32_t w = 0xeeaba2cc;

    hprime[0] = h[1];
    hprime[1] = h[2];
    hprime[2] = h[3];

    hprime[4] = h[5];
    hprime[5] = h[6];
    hprime[6] = h[7];

    uint32_t wire0 = EP0(h[1]);
    uint32_t wire1 = h[0] - wire0;
    uint32_t wire2 = MAJ(h[1], h[2], h[3]);
    uint32_t wire3 = wire1 - wire2;
    hprime[3] = h[4] - wire3;

    uint32_t wire4 = EP1(h[5]);
    uint32_t wire5 = wire3 - wire4;
    uint32_t wire6 = CH(h[5], h[6], h[7]);
    uint32_t wire7 = wire5 - wire6;
    uint32_t wire8 = k+w;
    hprime[7] = wire7 - wire8;

    for(i=0;i<8;i++){
        _dw(hprime[i]);
    }
    _endl;

//    _d(h3); 
//    _prn("ffb70472\n");

//    BYTE text1[] = {"abc"};
//    BYTE text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
//    BYTE text3[] = {"aaaaaaaaaa"};
//    BYTE hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
//                                     0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
//    BYTE hash2[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
//                                     0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
//    BYTE hash3[SHA256_BLOCK_SIZE] = {0xcd,0xc7,0x6e,0x5c,0x99,0x14,0xfb,0x92,0x81,0xa1,0xc7,0xe2,0x84,0xd7,0x3e,0x67,
//                                     0xf1,0x80,0x9a,0x48,0xa4,0x97,0x20,0x0e,0x04,0x6d,0x39,0xcc,0xc7,0x11,0x2c,0xd0};
//    BYTE buf[SHA256_BLOCK_SIZE];
//    SHA256_CTX ctx;
//    int idx;
//    int pass = 1;
//
//    sha256_init(&ctx);
//    sha256_update(&ctx, text1, strlen(text1));
//    sha256_final(&ctx, buf);
//    pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);

//    sha256_init(&ctx);
//    sha256_update(&ctx, text2, strlen(text2));
//    sha256_final(&ctx, buf);
//    pass = pass && !memcmp(hash2, buf, SHA256_BLOCK_SIZE);

//    sha256_init(&ctx);
//    for (idx = 0; idx < 100000; ++idx)
//       sha256_update(&ctx, text3, strlen(text3));
//    sha256_final(&ctx, buf);
//    pass = pass && !memcmp(hash3, buf, SHA256_BLOCK_SIZE);

//    printf("SHA-256 tests: %s\n", sha256_test() ? "SUCCEEDED" : "FAILED");

    return(0);
}
