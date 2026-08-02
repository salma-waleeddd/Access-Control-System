#ifndef _KYP_CONFIG_H
#define _KYP_CONFIG_H

#include"../../MCAL/DIO/DIO_Interface.h"
//init
#define KPD_ROW_PINS1_init    DIO_InitPin(Dio_GroupB,Dio_Pin4,Output);
#define KPD_ROW_PINS2_init    DIO_InitPin(Dio_GroupB,Dio_Pin5,Output);
#define KPD_ROW_PINS3_init    DIO_InitPin(Dio_GroupB,Dio_Pin6,Output);
#define KPD_ROW_PINS4_init    DIO_InitPin(Dio_GroupB,Dio_Pin7,Output);

#define KPD_COLUM_PINS1_init     DIO_InitPin(Dio_GroupD,Dio_Pin2,Input);
#define KPD_COLUM_PINS2_init     DIO_InitPin(Dio_GroupD,Dio_Pin3,Input);
#define KPD_COLUM_PINS3_init     DIO_InitPin(Dio_GroupD,Dio_Pin4,Input);
//write
#define KPD_ROW_PINS1_write      DIO_WritePin(Dio_GroupB,Dio_Pin4,High);
#define KPD_ROW_PINS2_write      DIO_WritePin(Dio_GroupB,Dio_Pin5,High);
#define KPD_ROW_PINS3_write      DIO_WritePin(Dio_GroupB,Dio_Pin6,High);
#define KPD_ROW_PINS4_write      DIO_WritePin(Dio_GroupB,Dio_Pin7,High);

#define KPD_COLUM_PINS1_write    DIO_WritePin(Dio_GroupD,Dio_Pin2,High);
#define KPD_COLUM_PINS2_write    DIO_WritePin(Dio_GroupD,Dio_Pin3,High);
#define KPD_COLUM_PINS3_write    DIO_WritePin(Dio_GroupD,Dio_Pin4,High);

#endif