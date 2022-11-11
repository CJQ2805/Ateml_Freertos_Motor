/*
 * CAN_CircularBuf.c
 *
 * Created: 2022/11/10 17:14:39
 *  Author: CJQ2805
 */ 
#include "CAN_CircularBuf.h"
#include "atmel_start.h"

t_can_circul_buf  g_tEXTID_can_circul_buf;  


int can_reset_buf(pt_can_circul_buf ptcircul_buf)
{
	if(NULL == ptcircul_buf)
	{
		SEGGER_RTT_printf(0,"the circul_buf is null \r\n");
		return -1;
	}
	ptcircul_buf->u8write_pos = ptcircul_buf->u8read_pos = 0;
	
	return 0;
}

int can_is_full(pt_can_circul_buf ptcircul_buf)
{
	if(NULL ==  ptcircul_buf)
	{
		SEGGER_RTT_printf(0,"the circul_buf is null \r\n");
		return 0;		
	}
	
	return	(((ptcircul_buf->u8write_pos + 1) % ptcircul_buf->u16CirulBufLen) == ptcircul_buf->u8read_pos);
}

int can_is_empty(pt_can_circul_buf ptcircul_buf)
{
	if(NULL == ptcircul_buf)
	{
		SEGGER_RTT_printf(0,"the circul_buf is null \r\n");
		return 0;
	}
	
	return (ptcircul_buf->u8write_pos == ptcircul_buf->u8read_pos);
}


int can_put_data(pt_can_circul_buf ptcircul_buf , pt_can_packet ptrx_packet)
{
	if( ( NULL == ptcircul_buf ) || ( NULL == ptrx_packet ) || ( NULL == ptcircul_buf->ptcircul_pact ))
	{
		SEGGER_RTT_printf(0,"put data is null \r\n");
		return -1;
	}

	if (can_is_full(ptcircul_buf))
	{
		return 0;
	}
	else
	{
		memcpy(&ptcircul_buf->ptcircul_pact[ptcircul_buf->u8write_pos] , ptrx_packet , sizeof(t_can_packet) );
		ptcircul_buf->u8write_pos = (ptcircul_buf->u8write_pos + 1) % ptcircul_buf->u16CirulBufLen;
		return 1;
	}
	
}



int can_take_data(pt_can_circul_buf ptcircul_buf, pt_can_packet ptrx_packet)
{

	if( ( NULL == ptcircul_buf ) || ( NULL == ptrx_packet ) )
	{
		SEGGER_RTT_printf(0,"the circul_buf is null \r\n");
		return -1;
	}


	if (can_is_empty(ptcircul_buf))
	return 0;
	else
	{
		memcpy(ptrx_packet , &ptcircul_buf->ptcircul_pact[ptcircul_buf->u8read_pos] , sizeof(t_can_packet));
		ptcircul_buf->u8read_pos = (ptcircul_buf->u8read_pos + 1) % ptcircul_buf->u16CirulBufLen;
		return 1;
	}
}


int can_rx_extid_data(struct can_message msg)
{
	t_can_packet     tpacket;
	tpacket.u32id = msg.id;
	tpacket.u8len = msg.len;
	memcpy(tpacket.au8data, msg.data, sizeof(tpacket.au8data));
	
	if(sizeof(tpacket.au8data) != msg.len)
	{
		for(uint8_t i = 0; i< (sizeof(tpacket.au8data) - msg.len); i++ )
		tpacket.au8data[i+msg.len] = 0x00;	
	}
		
	return can_put_data(&g_tEXTID_can_circul_buf, &tpacket);
}

//int can_rx_


int can_extid_circul_buf_empty(void)
{
	return can_is_empty(&g_tEXTID_can_circul_buf);
}

int can_stdid_circul_buf_empty(void)
{
	//return can_is_empty()
}