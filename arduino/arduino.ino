#include "CAN_driver.h"
#include "CAN_test.h"
#include "MCP2515_driver.h"
#include "servo_driver.h"


void setup()
{
	Serial.begin(9600);
	servo_init();
	
	CAN_init(MCP_MODE_NORMAL);
	delay(2000);
}

void loop()
{
	CanMessage_t resp;
	
	while(1)
	{
		resp = CAN_receive();
		if (resp.id == JOY_POSITION)
		{
			servo_joystick_control((int8_t) resp.data[1]);
		}
		CAN_print_message(&resp);
	}
}
