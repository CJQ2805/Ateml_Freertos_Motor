/*
 * CAN_CircularBuf.h
 *
 * Created: 2022/11/10 17:15:22
 *  Author: CJQ2805
 */ 
#ifndef CAN_CIRCULARBUF_H
#define CAN_CIRCULARBUF_H
#include "atmel_start.h"
typedef __PACKED  struct  _can_packet_t {

	uint32_t   u32id;
	uint8_t    u8len;
	uint8_t    au8data[8];

}t_can_packet, *pt_can_packet;

typedef struct _can_circul_buf_t {
	
	uint8_t  u8write_pos;
	uint8_t  u8read_pos;
	uint16_t u16CirulBufLen;
	pt_can_packet ptcircul_pact;
	
}t_can_circul_buf ,*pt_can_circul_buf;


int can_rx_extid_data(struct can_message msg);

#endif