/*
 * AFE_opr.c
 *
 * Created: 2022/10/3 16:27:29
 *  Author: CJQ2805
 */ 
#include "AFE_opr.h"
#include "SysConfig.h"

#define TASK_AFE_STACK_SIZE (128 / sizeof(portSTACK_TYPE))
#define TASK_AFE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedAFETask;

static void AFE_task(void *p)
{

	while (1) {

		//函数的执行内容
	}
}


void create_afe_task(void)
{
	taskENTER_CRITICAL();	
	if (xTaskCreate(
	AFE_task, "AFE", TASK_AFE_STACK_SIZE, NULL, TASK_AFE_STACK_PRIORITY, xCreatedAFETask)
	!= pdPASS) {
		while (1);
	}
	taskEXIT_CRITICAL(); 	
	
}