/*
 * CAN_driver.h
 *
 * Created: 30.09.2015 15:12:58
 *  Author: vegasten
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include "MCP2515_driver.h"
#include "util.h"

#define CAN_TR_CTRL_REG     0x30
#define CAN_TR_ID_ADDR_1    0x31
#define CAN_TR_ID_ADDR_2    0x32
#define CAN_TR_LEN_ADDR     0x35
#define CAN_TR_DATA_ADDR    0x36

#define CAN_TR_AVAILABLE    0b00001000

#define CAN_RCV_CTRL_REG    0x60
#define CAN_RCV_ID_ADDR_1   0x61
#define CAN_RCV_ID_ADDR_2   0x62
#define CAN_RCV_LEN_ADDR    0x65
#define CAN_RCV_DATA_ADDR   0x66

#define CAN_RCV_MASK        0b01100100
#define CAN_RCV_NO_FILTERS  0b01100000
#define CAN_RCV_NO_ROLLOVER 0b00000100


struct CanMessage
{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
};
typedef struct CanMessage CanMessage_t;

void CAN_init(uint8_t mode);
void CAN_send(CanMessage_t* message);
CanMessage_t CAN_receive();

#endif /* CAN_DRIVER_H_ */