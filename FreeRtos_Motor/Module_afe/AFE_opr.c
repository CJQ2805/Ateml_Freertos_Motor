/*
 * AFE_opr.c
 *
 * Created: 2022/10/3 16:27:29
 *  Author: CJQ2805
 */ 

#include "FreeRTOS.h"
#include "atmel_start.h"
#include "task.h"

#define TASK_AFE_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_AFE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedAFETask;
static uint32_t  u32afe_cnt = 0;
static void AFE_task(void *p)
{

	while (1) {
	
		u32afe_cnt++;
		gpio_set_pin_level(LED_PIN , false);
		SEGGER_RTT_printf(0,"u32afe_cnt = %d \r\n",u32afe_cnt);
		vTaskDelay(1);
		//函数的执行内容
	}
}


void create_afe_task(void)
{
	taskENTER_CRITICAL();	
	if (xTaskCreate(AFE_task, 
					"AFE", 
					TASK_AFE_STACK_SIZE, 
					NULL, 
					TASK_AFE_STACK_PRIORITY, 
					xCreatedAFETask)
	!= pdPASS) {
		while (1);
	}
	taskEXIT_CRITICAL(); 	
	
}