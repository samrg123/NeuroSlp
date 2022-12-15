/*
Copyright (c) 2019, Ameer Haj Ali (UC Berkeley), and Intel Corporation
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "header.h"

short sa[128];
short sb[128];
int   out1[128] ALIGNED16;
int   out2[128] ALIGNED16;

__attribute__((noinline))
void example(short *__restrict__ sa, short *__restrict__ sb, int* __restrict__ out1, int* __restrict__ out2) {
  int i;
#pragma unroll(512)
  for (i = 0; i < 128-1; i+=2) {
    out1[i] = (int) sa[i];
out1[i+1] = (int) sa[i+1];
    out2[i] = (int) sb[i];
out2[i+1] = (int) sb[i+1];
  }
}
int main(int argc,char* argv[]){
  init_memory(&out1[0], &out1[128]);
  init_memory(&out2[0], &out2[128]);
  init_memory(&sa[0], &sa[128]);
  init_memory(&sb[0], &sb[128]);
  BENCH("Example10b", example(sa,sb,out1,out2), Mi*4/128*512, digest_memory(&out1[0], &out1[128])+digest_memory(&out2[0], &out2[128]));
 
  return 0;
}
