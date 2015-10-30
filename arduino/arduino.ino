#include "CAN_driver.h"
#include "CAN_test.h"
#include "MCP2515_driver.h"
#include "ir_driver.h"
#include "servo_driver.h"
#include <Wire/Wire.h>
#include "motor_driver.h"

unsigned long start, current;
int score = 0;

void setup()
{
	Serial.begin(9600);
	
	ir_init();
	servo_init();
	
	//CAN_test_normal_receive();
	
	CAN_init(MCP_MODE_NORMAL);
	delay(2000);
}

void loop()
{
	CanMessage_t resp;
	
	while(1)
	{
		start = millis();
		resp = CAN_receive();
		if (resp.id == JOY_POSITION)
		{
			servo_joystick_control((int8_t) resp.data[1]);
			//CAN_print_message(&resp);
		}
		
		if (ir_check() == 1)
		{
			CanMessage_t message;
			message.id = SCORE;
			message.length = 1;
			message.data[0] = score;
			//CAN_send(&message);
			Serial.print("Score updated: ");
			Serial.println(score);
			delay(1000);
			score = 0;
		}
		
		current = millis();
		score += (int)(current - start);
	}
}
