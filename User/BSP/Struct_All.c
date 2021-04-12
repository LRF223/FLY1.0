//#include "EEPROM.h"
#include "struct_all.h"

struct _acc  acc;			//ԭʼ����
struct _gyro gyro;
////////////////////////////////////////////
struct _acc  filter_acc;	//�˲�������
struct _gyro filter_gyro;
////////////////////////////////////////////
struct _acc  offset_acc;	//��ƫ����
struct _gyro offset_gyro;
////////////////////////////////////////////
struct _SI_float  SI_acc;	//���ٶ����ݣ�m/s2��
struct _SI_float  SI_gyro;	//���ٶ����ݣ�rad��
////////////////////////////////////////////
struct _Rc Rc;				//ң��ͨ��
struct _out_angle out_angle;//��̬����-�Ƕ�ֵ

/* pid */
struct _pid pitch;
struct _pid roll;
struct _pid gyro_pitch;
struct _pid gyro_roll;
struct _pid gyro_yaw;



///////////////////////////////////////////////////////////
#define EEPROM_offset_acc_x		0
#define EEPROM_offset_acc_y		1
#define EEPROM_offset_acc_z		2
#define EEPROM_offset_gyro_x	3
#define EEPROM_offset_gyro_y	4
#define EEPROM_offset_gyro_z	5
#define EEPROM_PID_ROL_P		6
#define EEPROM_PID_ROL_I		7
#define EEPROM_PID_ROL_D		8
#define EEPROM_PID_PIT_P		9
#define EEPROM_PID_PIT_I		10
#define EEPROM_PID_PIT_D		11
#define EEPROM_PID_YAW_P		12
#define EEPROM_PID_YAW_I		13
#define EEPROM_PID_YAW_D		14
#define EEPROM_SUM				15


//void EEPROM_READ_ACC_OFFSET(void)	//��ȡacc��ƫ
//{
//	EE_ReadVariable(VirtAddVarTab[EEPROM_offset_acc_x], &data_x);
//	EE_ReadVariable(VirtAddVarTab[EEPROM_offset_acc_y], &data_y);
//	EE_ReadVariable(VirtAddVarTab[EEPROM_offset_acc_z], &data_z);
//	offset_acc.x = (int16_t) data_x;
//	offset_acc.y = (int16_t) data_y;
//	offset_acc.z = (int16_t) data_z;
//}
//void EEPROM_SAVE_GYRO_OFFSET(void)	//����gyro��ƫ
//{
//	 __set_PRIMASK(1);//��ȫ���ж�
//	EE_WriteVariable(VirtAddVarTab[EEPROM_offset_gyro_x], offset_gyro.x);
//	EE_WriteVariable(VirtAddVarTab[EEPROM_offset_gyro_y], offset_gyro.y);
//	EE_WriteVariable(VirtAddVarTab[EEPROM_offset_gyro_z], offset_gyro.z);
//	 __set_PRIMASK(0);//���ж�
//}
