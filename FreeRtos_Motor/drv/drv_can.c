/*
 * drv_can.c
 *
 * Created: 2022/11/10 10:27:20
 *  Author: CJQ2805
 */ 

#include "drv_can.h"
#include <atmel_start.h>

uint32_t u32cnt = 0;

void CAN1_tx_callback(struct can_async_descriptor *const descr)
{
	(void)descr;
}

void CAN1_rx_callback(struct can_async_descriptor *const descr)
{

	struct can_message msg;
	uint8_t            data[64];
	msg.data = data;
	can_async_read(descr, &msg);
	
	if(CAN_FMT_STDID == msg.fmt)
	{
		u32cnt++;
		//SEGGER_RTT_printf(0,"CAN ID IS CAN_FMT_STDID \r\n");
		//SEGGER_RTT_printf(0,"CAN ID  = %08x \r\n", msg.id);
	}
	else if(CAN_FMT_EXTID == msg.fmt)
	{
		u32cnt++;
		//SEGGER_RTT_printf(0,"CAN ID IS CAN_FMT_EXTID \r\n");
		//SEGGER_RTT_printf(0,"CAN ID  = %08x \r\n", msg.id);
	}
	
	//for (uint8_t i =0; i < msg.len; i++)
	//{
		//SEGGER_RTT_printf(0,"CAN1 data = %02x \r\n", msg.data[i]);	
	//}
	
	return;
}


void CAN1_Init(void)
{
	struct can_message msg;
	struct can_filter  filter;
	uint8_t            send_data[4];
	send_data[0] = 0x00;
	send_data[1] = 0x01;
	send_data[2] = 0x02;
	send_data[3] = 0x03;

	msg.id   = 0x45A;
	msg.type = CAN_TYPE_DATA;
	msg.data = send_data;
	msg.len  = 4;
	msg.fmt  = CAN_FMT_STDID;
	can_async_register_callback(&CAN_1, CAN_ASYNC_TX_CB, (FUNC_PTR)CAN1_tx_callback);
	can_async_enable(&CAN_1);

	/**
	 * CAN_1_tx_callback callback should be invoked after call
	 * can_async_write, and remote device should recieve message with ID=0x45A
	 */
	can_async_write(&CAN_1, &msg);

	msg.id  = 0x100000A5;
	msg.fmt = CAN_FMT_EXTID;
	/**
	 * remote device should recieve message with ID=0x100000A5
	 */
	can_async_write(&CAN_1, &msg);

	/**
	 * CAN_1_rx_callback callback should be invoked after call
	 * can_async_set_filter and remote device send CAN Message with the same
	 * content as the filter.
	 */
	can_async_register_callback(&CAN_1, CAN_ASYNC_RX_CB, (FUNC_PTR)CAN1_rx_callback);
	filter.id   = 0x469;
	filter.mask = 0;
	can_async_set_filter(&CAN_1, 0, CAN_FMT_STDID, &filter);

	filter.id   = 0x10000096;
	filter.mask = 0;
	can_async_set_filter(&CAN_1, 1, CAN_FMT_EXTID, &filter);
}
