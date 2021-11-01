// =============================================================================
//  Program : string.c
//  Author  : Chun-Jen Tsai
//  Date    : Dec/09/2019
// -----------------------------------------------------------------------------
//  Description:
//  This is the minimal string library for aquila.
// -----------------------------------------------------------------------------
//  Revision information:
//
//  Oct/6/2020, by Chun-Jen Tsai:
//    Replace strcpy(), strncpy(), strncmp(), and strcmp() with code extracted
//    from the RISC-V port of Newlib at https://github.com/riscv/riscv-newlib.
//    These functions boost DMIPS by 28.5%.
// -----------------------------------------------------------------------------
//  License information:
//
//  This software is released under the BSD-3-Clause Licence,
//  see https://opensource.org/licenses/BSD-3-Clause for details.
//  In the following license statements, "software" refers to the
//  "source code" of the complete hardware/software system.
//
//  Copyright 2019,
//                    Embedded Intelligent Systems Lab (EISL)
//                    Deparment of Computer Science
//                    National Chiao Tung Uniersity
//                    Hsinchu, Taiwan.
//
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
// =============================================================================
#include <stdio.h>
#include <string.h>

// ------------------------------------------------------------------------------
//  Functions extracted from Newlib.
//
#define UNALIGNED(X,Y) (((long)X & (sizeof(long)-1))|((long)Y & (sizeof(long)-1)))
#define DETECTNULL(X) (((X)-0x01010101) & ~(X) & 0x80808080)

char *strcpy(char *dst, char *src)
{
    
    char *dst0 = dst;
    const char *src0 = src;
    long *aligned_dst;
    const long *aligned_src;

    // If SRC or DEST is unaligned, then copy bytes.
    if (!UNALIGNED(src0, dst0))
    {
        aligned_dst = (long *) dst0;
        aligned_src = (long *) src0;

        // Perform word copying since both strings are word-aligned.
        while (!DETECTNULL(*aligned_src))
        {
            *aligned_dst++ = *aligned_src++;
        }

        dst0 = (char *) aligned_dst;
        src0 = (char *) aligned_src;
    }

    // Copying trailing bytes for aligned strings, or the entire
    // strings if not aligned.
    while ((*dst0++ = *src0++)) ;

    return dst;
   /*
    char *tmp0 = dst;
    char *tmp1 = dst+1;
    char *tmp2 = dst+2;
    
    char *src0 = src;
    char *src1 = src+1;
    char *src2 = src+2;
    
    while (*src0) {
       *tmp0 = *src0;
       *tmp1 = *src1;
       *tmp2 = *src2;
       src0 += 3;
       tmp0 += 3;
       src1 += 3;
       tmp1 += 3;
       src2 += 3;
       tmp2 += 3;
       if (!(*src0)) break;
       else if (!(*src1)) {
           *tmp0 = *src0;
           break;
       }
       else if (!(*src2)) {
           *tmp0 = *src0;
           *tmp1 = *src1;
           break;
       }
   }
   
   *tmp0 = 0;
   *tmp1 = 0;
   *tmp2 = 0;
   *src0 = 0;
   *src1 = 0;
   *src2 = 0;

   return dst;
    */
}

int strcmp(char *s1, char *s2)
{
    /*
    unsigned long *a1;
    unsigned long *a2;

    // If s1 or s2 are unaligned, then compare bytes.
    if (!UNALIGNED(s1, s2))
    {
        // If s1 and s2 are word-aligned, compare them a word at a time.
        a1 = (unsigned long *) s1;
        a2 = (unsigned long *) s2;
        while (*a1 == *a2)
        {
            // To get here, *a1 == *a2, thus if we find a null in *a1, then the strings must be equal, so return zero.
            if (DETECTNULL(*a1))
                return 0;

            a1++;
            a2++;
        }

        // A difference was detected in last few bytes of s1, so search bytewise
        s1 = (char *) a1;
        s2 = (char *) a2;
    }

    while (*s1 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *) s1) - (*(unsigned char *) s2);*/
    
    int value;
 
    char *s1_0 = s1;
    char *s1_1 = s1-3;
    char *s1_2 = s1-2;
    char *s1_3 = s1-1;

    char *s2_0 = s2;
    char *s2_1 = s2-3;
    char *s2_2 = s2-2;
    char *s2_3 = s2-1;

    do {
        s1_2 += 4, s2_2 += 4;

        if (*s1_0 == *s2_0) {
            value = 0;
        }
        else if (*s1_0 < *s2_0) {
            value = -1;
            break;
        }
        else {
            value = 1;
            break;
        }

        if (!(*s1_0) || !(*s2_0)) break;
        s1_3 += 4, s2_3 += 4;

        if (*s1_1 == *s2_1) {
            value = 0;
        }
        else if (*s1_1 < *s2_1) {
            value = -1;
            break;
        }
        else {
            value = 1;
            break;
        }

        if (!(*s1_1) || !(*s2_1)) break;
        s1_0 += 4, s2_0 += 4;

        if (*s1_2 == *s2_2) {
            value = 0;
        }
        else if (*s1_2 < *s2_2) {
            value = -1;
            break;
        }
        else {
            value = 1;
            break;
        }

        if (!(*s1_2) || !(*s2_2)) break;
        s1_1 += 4, s2_1 += 4;

        if (*s1_3 == *s2_3) {
            value = 0;
        }
        else if (*s1_3 < *s2_3) {
            value = -1;
            break;
        }
        else {
            value = 1;
            break;
        }

        if (!(*s1_3) || !(*s2_3)) break;

    } while (1);

    *s1_0 = 0, *s1_1 = 0, *s1_2 = 0;
    *s2_0 = 0, *s2_1 = 0, *s2_2 = 0;

    return value;
}

char *strncpy(char *dst, char *src, size_t n)
{
    char *dst0 = dst;
    const char *src0 = src;
    long *aligned_dst;
    const long *aligned_src;

    // If SRC or DEST is unaligned, then copy bytes.
    if (!UNALIGNED(src0, dst0))
    {
        aligned_dst = (long *) dst0;
        aligned_src = (long *) src0;

        // Perform word copying since both strings are word-aligned.
        while (!DETECTNULL(*aligned_src) && n > sizeof(long))
        {
            *aligned_dst++ = *aligned_src++;
            n -= sizeof(long);
        }

        dst0 = (char *) aligned_dst;
        src0 = (char *) aligned_src;
    }

    // Copying trailing bytes for aligned strings, or the entire
    // strings if not aligned.
    while ((*dst0++ = *src0++) && n-- > 0) ;
    if (++n == 0) *dst0 = 0;

    return dst;
    /*
    char *tmp = dst;

    while (*src && n) *(tmp++) = *(src++), n--;
    while (n--) *(tmp++) = 0;
    return dst;
    */
}

int strncmp(char *s1, char *s2, size_t n)
{
    unsigned long *a1;
    unsigned long *a2;

    // If s1 or s2 are unaligned, then compare bytes.
    if (!UNALIGNED(s1, s2))
    {
        // If s1 and s2 are word-aligned, compare them a word at a time.
        a1 = (unsigned long *) s1;
        a2 = (unsigned long *) s2;
        while (*a1 == *a2 && n > sizeof(long))
        {
            // To get here, *a1 == *a2, thus if we find a null in *a1, then the strings must be equal, so return zero.
            if (DETECTNULL(*a1))
                return 0;

            a1++;
            a2++;
            n -= sizeof(long);
        }

        // A difference was detected in last few bytes of s1, so search bytewise
        s1 = (char *) a1;
        s2 = (char *) a2;
    }

    while (n && *s1 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
        n--;
    }
    return (*(unsigned char *) s1) - (*(unsigned char *) s2);
    /*
    int value;

    s1--, s2--;
    do
    {
        s1++, s2++;
        if (*s1 == *s2)
        {
            value = 0;
        }
        else if (*s1 < *s2)
        {
            value = -1;
            break;
        }
        else
        {
            value = 1;
            break;
        }
    } while (--n && *s1 != 0 && *s2 != 0);
    return value;*/
}

void *memcpy(void *d, void *s, size_t n)
{
    char *d0 = d;
    const char *s0 = s;
    long *aligned_d;
    const long *aligned_s;

    // If SRC or DEST is unaligned, then copy bytes.
    if (!UNALIGNED(s0, d0))
    {
        aligned_d = (long *) d0;
        aligned_s = (long *) s0;

        // Perform word copying since both pointers are word-aligned.
        while (!DETECTNULL(*aligned_s) && n > sizeof(long))
        {
            *aligned_d++ = *aligned_s++;
            n -= sizeof(long);
        }

        d0 = (char *) aligned_d;
        s0 = (char *) aligned_s;
    }

    // Copying trailing bytes for aligned memory block, or the entire
    // memory block if not aligned.
    while ((*d0++ = *s0++) && n-- > 0) ;
    if (++n == 0) *d0 = 0;

    return d;
    /*
    unsigned char *dst = (unsigned char *) d;
    unsigned char *src = (unsigned char *) s;

    for (int idx = 0; idx < n; idx++) *(dst++) = *(src++);
    return d;*/
}

//  End of functions extracted from Newlib.
// ------------------------------------------------------------------------------

void *memmove(void *d, void *s, size_t n)
{
    unsigned char *dst = (unsigned char *) d + n - 1;
    unsigned char *src = (unsigned char *) s + n - 1;

    if ((unsigned) d >= (unsigned) s && (unsigned) d <= (unsigned) s + n)
    {
        while (n--) *(dst--) = *(src--);
    }
    else memcpy(d, s, n);

    return d;
    /*
    unsigned char *dst = (unsigned char *) d;
    unsigned char *src = (unsigned char *) s;

    if ((unsigned) d >= (unsigned) s &&
        (unsigned) d <= (unsigned) s + n)
    {
        for (int idx = n - 1; idx >= 0; idx--) dst[idx] = src[idx];
    }
    else
    {
        for (int idx = 0; idx < n; idx++) *(dst++) = *(src++);
    }

    return d;*/
}

void *memset(void *d, int v, size_t n)
{
    
    unsigned char *dst = (unsigned char *) d;

    while (n--) *(dst++) = (unsigned char) v;
    return d;
    /*
    unsigned char *dst = (unsigned char *) d;

    for (int idx = 0; idx < n; idx++) *(dst++) = (unsigned char) v;
    return d;*/
}

long strlen(char *s)
{
    long n = 0;

    while (*s++) n++;
    return n;
}

char *strcat(char *dst, char *src)
{
    char *tmp = dst;

    while (*tmp) tmp++;
    while (*src) *(tmp++) = *(src++);
    *tmp = 0;
    return dst;
}

char *strncat(char *dst, char *src, size_t n)
{
    char *tmp = dst;

    while (*tmp) tmp++;
    while (*src && n) *(tmp++) = *(src++), n--;
    *tmp = 0;
    return dst;
}


