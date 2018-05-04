#include "arm_math.h"
#include "arm_const_structs.h"
#include "stdio.h"

//260 40 最大重心高度 平衡足心点
//0 150 步距
// 220 平时高度

#define MATRIX_VAL(p,r,c) *(((p)->pData) + (c) + (p)->numCols *(r))

typedef struct{
	float32_t a;
	float32_t alpha;
	float32_t d;
	float32_t theta;
}D_H_instance;

void get_D_H_matrix(arm_matrix_instance_f32 *pmat,D_H_instance *pd_h){
	MATRIX_VAL(pmat,0,0) = arm_cos_f32(pd_h->theta);
	MATRIX_VAL(pmat,0,1) = -arm_sin_f32(pd_h->theta)*arm_cos_f32(pd_h->alpha);
	MATRIX_VAL(pmat,0,2) = arm_sin_f32(pd_h->theta)*arm_sin_f32(pd_h->alpha);
	MATRIX_VAL(pmat,0,3) = pd_h->a*arm_cos_f32(pd_h->theta);

	MATRIX_VAL(pmat,1,0) = arm_sin_f32(pd_h->theta);
	MATRIX_VAL(pmat,1,1) = arm_cos_f32(pd_h->theta)*arm_cos_f32(pd_h->alpha);
	MATRIX_VAL(pmat,1,2) = -arm_cos_f32(pd_h->theta)*arm_sin_f32(pd_h->alpha);
	MATRIX_VAL(pmat,1,3) = pd_h->a*arm_sin_f32(pd_h->theta);

	MATRIX_VAL(pmat,2,0) = 0;
	MATRIX_VAL(pmat,2,1) = arm_sin_f32(pd_h->alpha);
	MATRIX_VAL(pmat,2,2) = arm_cos_f32(pd_h->alpha);
	MATRIX_VAL(pmat,2,3) = pd_h->d;

	MATRIX_VAL(pmat,3,0) = 0;
	MATRIX_VAL(pmat,3,1) = 0;
	MATRIX_VAL(pmat,3,2) = 0;
	MATRIX_VAL(pmat,3,3) = 1;
}


void CalMatrix(float *joint_theta,arm_matrix_instance_f32 *H){
	float32_t A_buff[16] = {0.0f};
	float32_t B_buff[16] = {0.0f};
	float32_t C_buff[16] = {0.0f};
	float32_t D_buff[16] = {0.0f};
	float32_t E_buff[16] = {0.0f};
	float32_t F_buff[16] = {0.0f};
	float32_t G_buff[16] = {0.0f};
	float32_t length[6] = {25,37,51,59,44,0};
	//float32_t length[6] = {10,10,10,10,10,0};

	arm_matrix_instance_f32 A;
	arm_matrix_instance_f32 B;
	arm_matrix_instance_f32 C;
	arm_matrix_instance_f32 D;
	arm_matrix_instance_f32 E;
	arm_matrix_instance_f32 F;
	arm_matrix_instance_f32 G;

	arm_mat_init_f32(&A,4,4,A_buff);
	arm_mat_init_f32(&B,4,4,B_buff);
	arm_mat_init_f32(&C,4,4,C_buff);
	arm_mat_init_f32(&D,4,4,D_buff);
	arm_mat_init_f32(&E,4,4,E_buff);
	arm_mat_init_f32(&F,4,4,F_buff);
	arm_mat_init_f32(&G,4,4,G_buff);

	D_H_instance D_H_1 = {         0, -PI/2, length[0],  PI/2+0 			};
	D_H_instance D_H_2 = { length[1], -PI/2,         0, -PI/2+joint_theta[0]};
	D_H_instance D_H_3 = { length[2],     0,         0,     0+joint_theta[1]};
	D_H_instance D_H_4 = { length[3],     0,         0,     0+joint_theta[2]};
	D_H_instance D_H_5 = { length[4],  PI/2,         0,     0+joint_theta[3]};
	D_H_instance D_H_6 = {         0,  PI/2,         0,  PI/2+joint_theta[4]};

	get_D_H_matrix(&A,&D_H_1);
	get_D_H_matrix(&B,&D_H_2);
	get_D_H_matrix(&C,&D_H_3);
	get_D_H_matrix(&D,&D_H_4);
	get_D_H_matrix(&E,&D_H_5);
	get_D_H_matrix(&F,&D_H_6);

	arm_mat_mult_f32(&A,&B,&G);
	arm_mat_mult_f32(&G,&C,&A);
	arm_mat_mult_f32(&A,&D,&B);
	arm_mat_mult_f32(&B,&E,&C);
	arm_mat_mult_f32(&C,&F,H);
}


int main(){

	float32_t H_buff[16] = {0.0f};
	//float32_t length[6] = {25,37,51,59,44,0};
	float32_t joint_theta[5] = {PI/16,0,0,0,-PI/16};

	float32_t ol1 = 0;
	float32_t ol2 = 0;
	float32_t ol3 = 0;

	arm_matrix_instance_f32 H;
	arm_mat_init_f32(&H,4,4,H_buff);


	CalMatrix(joint_theta,&H);
	ol1 = atan2( MATRIX_VAL(&H,1,2)
			   , MATRIX_VAL(&H,0,2));

	ol2 = atan2(-MATRIX_VAL(&H,0,0)*arm_sin_f32(ol1)+MATRIX_VAL(&H,1,0)*arm_cos_f32(ol1)
			   ,-MATRIX_VAL(&H,0,1)*arm_sin_f32(ol1)+MATRIX_VAL(&H,1,1)*arm_cos_f32(ol1));

	ol3 = atan2( MATRIX_VAL(&H,0,2)*arm_cos_f32(ol1)+MATRIX_VAL(&H,1,2)*arm_sin_f32(ol1)
	           , MATRIX_VAL(&H,2,2));
	
	return 0;
}