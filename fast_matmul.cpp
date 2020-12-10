#include "stdafx.h"
#include <iostream>
#include<stdint.h>
#include<intrin.h>
using namespace std;
//intput[N][M], weight[M][K], output[N][K]
void fast_mat_mul(float** input, float** weight, float** output, int N, int M, int K)
{
	for(int i=0;i<N;i++){
		for(int j=0;j<K;j++){
			output[i][j]=0;
		}
	}
	if(K>=4&&K%4==0){
	__m128 value0_sse,tmp1, tmp2;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			value0_sse = _mm_set_ps1(input[i][j]);
			for(int k=0;k<K;k+=4){
				tmp1 = _mm_mul_ps(value0_sse, _mm_load_ps(&weight[j][k]));
				tmp2 = _mm_add_ps(tmp1,_mm_load_ps(&output[i][k]));
				_mm_store_ps(&output[i][k], tmp2);
			}
		}
	}
	}
	else{
	float tmp=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			for(int k=0;k<K;k++){
				output[i][k]+=input[i][j]*weight[j][k];
			}
		}
	}
	}
}
