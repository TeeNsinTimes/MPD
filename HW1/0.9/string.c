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
//  None.
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

void *memcpy(void *d, void *s, size_t n)
{
    unsigned char *dst = (unsigned char *) d;
    unsigned char *src = (unsigned char *) s;

    for (int idx = 0; idx < n; idx++) *(dst++) = *(src++);
    return d;
}

void *memmove(void *d, void *s, size_t n)
{
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

    return d;
}

void *memset(void *d, int v, size_t n)
{
    unsigned char *dst = (unsigned char *) d;

    for (int idx = 0; idx < n; idx++) *(dst++) = (unsigned char) v;
    return d;
}

long strlen(char *s)
{
    long n = 0;

    while (*s++) n++;
    return n;
}

/*hw1_modify*/
char *strcpy(char *dst, char *src)
{
    
    char *tmp = dst;

    while (*src) *(tmp++) = *(src++);
    *tmp = 0;
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

char *strncpy(char *dst, char *src, size_t n)
{
    char *tmp = dst;

    while (*src && n) *(tmp++) = *(src++), n--;
    while (n--) *(tmp++) = 0;
    return dst;
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

/*hw1_modify*/
int  strcmp(char *s1, char *s2)
{
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
    } while (*s1 && *s2);
    return value;*/
    
    int value;
 
    char *s1_0 = s1;
    char *s1_1 = s1-1;
    char *s1_2 = s1-2;

    char *s2_0 = s2;
    char *s2_1 = s2-1;
    char *s2_2 = s2-2;

    do {
        //s1_1 += 2, s2_1 += 2;
        s1_1 += 3, s2_1 += 3;

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
        s1_2 += 3, s2_2 += 3;
        //s1_0 += 2, s2_0 += 2;

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
        s1_0 += 3, s2_0 += 3;

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

    } while (1);

    *s1_0 = 0, *s1_1 = 0, *s1_2 = 0;
    *s2_0 = 0, *s2_1 = 0, *s2_2 = 0;

    return value;
    
}

int  strncmp(char *s1, char *s2, size_t n)
{
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
    return value;
}
