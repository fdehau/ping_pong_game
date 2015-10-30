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
#include <Arduino.h>
#include <HardwareSerial.h>

#define CAN_TR_CTRL_REG     0x30
#define CAN_TR_REQUEST      0b00001000
#define CAN_TR_ERR          0b00010000
#define CAN_TR_MLOA         0b00100000
#define CAN_TR_ABTF         0b01000000

#define CAN_TR_ID_ADDR_1    0x31
#define CAN_TR_ID_ADDR_2    0x32
#define CAN_TR_LEN_ADDR     0x35
#define CAN_TR_DATA_ADDR    0x36

#define CAN_RCV_CTRL_REG    0x60
#define CAN_RCV_ID_ADDR_1   0x61
#define CAN_RCV_ID_ADDR_2   0x62
#define CAN_RCV_LEN_ADDR    0x65
#define CAN_RCV_DATA_ADDR   0x66

#define CAN_RCV_MASK        0b01100100
#define CAN_RCV_NO_FILTERS  0b01100000
#define CAN_RCV_NO_ROLLOVER 0b00000100

enum CanMsgId {
	DEFAULT_ID,
	JOY_POSITION,
	SCORE
};

struct CanMessage
{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
};
typedef struct CanMessage CanMessage_t;

uint8_t CAN_init(uint8_t mode);
uint8_t CAN_send(CanMessage_t* message);
CanMessage_t CAN_receive();
void CAN_print_message(CanMessage_t* msg);

#endif /* CAN_DRIVER_H_ */