/*
 * freertos.c
 *
 * Created: 2022/10/3 16:10:00
 *  Author: CJQ2805
 */ 
#include "freertos.h"

void FREERTOS_Init(void)
{
	//CJQ2805 FreeRTOS是移植的，非配置。采用FreeRTOS V10.2.1版本
	start_tasks();
}


void start_tasks(void)
{
	create_afe_task();
	create_comm_task();
	
	vTaskStartScheduler();
}