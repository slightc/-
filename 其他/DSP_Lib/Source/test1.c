#include "arm_math.h"
#include "arm_const_structs.h"
#include "stdio.h"

float32_t A_buff[16] = {0.0f};


#define MATRIX_VAL(p,r,c) *(((p)->pData) + (c) + (p)->numCols *(r))

int main(){
	arm_matrix_instance_f32 A;
	arm_mat_init_f32(&A,2,8,A_buff);
	MATRIX_VAL(&A,1,0) = 2;
	return 0;
}