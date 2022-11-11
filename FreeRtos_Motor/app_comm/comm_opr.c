/*
 * comm_opr.c
 *
 * Created: 2022/11/11 10:34:58
 *  Author: CJQ2805
 */ 


#include "FreeRTOS.h"
#include "atmel_start.h"
#include "task.h"

#define TASK_COMM_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_COMM_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedCOMMTask;

static uint32_t u32comm_cnt = 0;
static void comm_task(void *p)
{

	while (1) {
		u32comm_cnt++;
		gpio_set_pin_level(LED_PIN, true);
		SEGGER_RTT_printf(0,"u32comm_cnt = %d \r\n",u32comm_cnt);
		vTaskDelay(1);
		//函数的执行内容
	}
}


void create_comm_task(void)
{
	taskENTER_CRITICAL();
	if (xTaskCreate(comm_task, 
					"comm", 
					TASK_COMM_STACK_SIZE, 
					NULL, 
					TASK_COMM_STACK_PRIORITY, 
					xCreatedCOMMTask)
	!= pdPASS) {
		while (1);
	}
	taskEXIT_CRITICAL();
	
}