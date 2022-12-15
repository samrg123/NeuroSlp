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

int output[256] ALIGNED16;
int input1[256] ALIGNED16;
int input2[256] ALIGNED16;

__attribute__((noinline))
void example () {
   int i;

   /* feature: support for read accesses with a compile time known misalignment  */
#pragma unroll(512)
   for (i=0; i<256-4; i+=2){
      output[i] = input1[i+1] *input2[i+3];
      output[i+1]=input1[i] *input2[i+2];
   }
}

int main(int argc,char* argv[]){
  init_memory(&output[0], &output[256]);
  init_memory(&input1[0], &input1[256]);
  init_memory(&input2[0], &input2[256]);
 
  BENCH("Example4b",  example(), Mi*2/256*512, digest_memory(&output[0], &output[256]));
  
  return 0;
}
