#ifndef __TBZ_MPU6050_H_
#define __TBZ_MPU6050_H_

#ifdef __cplusplus
extern "C" {
#endif
void MPU6050_Init(void);
void MPU6050_Read_Accel(void);
void MPU6050_Read_Gyro(void);
void MPU6050_Read_Temp(void);
extern float Ax,Ay,Az,Gx,Gy,Gz,Temp;

#ifdef __cplusplus
}
#endif
#endif
