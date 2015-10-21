/*
 * CAN_test.c
 *
 * Created: 21.10.2015 13:00:47
 *  Author: vegasten
 */ 

#include "CAN_test.h"

void CAN_test_loopback()
{
	CAN_init(MCP_MODE_LOOPBACK);
	
	CanMessage_t message;
	CanMessage_t resp;
	message.id = 15;
	message.length = 4;
	message.data[0] = 'T';
	message.data[1] = 'E';
	message.data[2] = 'S';
	message.data[3] = 'T';
	while(1)
	{
		CAN_send(&message);
		_delay_ms(200);
		resp = CAN_receive();
		CAN_print_message(&resp);
	}
}

void CAN_test_normal_send(){
	
	CAN_init(MCP_MODE_NORMAL);
	
	CanMessage_t message;
	message.id = 15;
	message.length = 4;
	message.data[0] = 'T';
	message.data[1] = 'E';
	message.data[2] = 'S';
	message.data[3] = 'T';
	while(1)
	{
		CAN_send(&message);
		printf("Message sent!\n");
		_delay_ms(200);
	}
}
void CAN_test_normal_receive()
{
	CAN_init(MCP_MODE_NORMAL);
	
	CanMessage_t resp;
	
	while(1)
	{
		_delay_ms(200);
		resp = CAN_receive();
		CAN_print_message(&resp);
	}
}
