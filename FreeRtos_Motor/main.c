#include "atmel_start.h"
#include "freertos.h"
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	TIMER_0_example();
//	CAN_0_example();
	CAN1_Init();
	 

	FREERTOS_Init();
	
	/* Replace with your application code */
	while (1) {
			
		//SEGGER_RTT_printf(0,"cnt = %d\r\n", u32cnt);
	}
}
