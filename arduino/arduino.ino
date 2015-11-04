#include "CAN_driver.h"
#include "CAN_test.h"
#include "MCP2515_driver.h"
#include "ir_driver.h"
#include "servo_driver.h"
#include <Wire/Wire.h>
#include "motor_driver.h"

unsigned long start, current;
uint32_t score = 0;

void setup()
{
	CAN_init(MCP_MODE_NORMAL);
	
	ir_init();
	servo_init();
	motor_init();
	
	Serial.begin(9600);
}
#define SCORE_TIMEOUT 1000

void loop()
{
	CanMessage_t resp;
	
	uint32_t last_ball = 0;
	
	while(1)
	{
		
		start = millis();
		resp = CAN_receive();
		if (resp.id == JOY_POSITION)
		{
			servo_joystick_control((int8_t) resp.data[1]);
			motor_control((int8_t) resp.data[1]);
			//CAN_print_message(&resp);
		}
		
		if (ir_check() == 1)
		{
			Serial.println(millis() - last_ball);
			if((millis() - last_ball) > SCORE_TIMEOUT){
				CanMessage_t message;
				message.id = SCORE;
				message.length = 2;
				message.data[0] = score >> 8;
				message.data[1] = score;
				CAN_send(&message);
				Serial.print("Score updated: ");
				Serial.println(score);
				score = 0;
			}
			last_ball = millis();
		}
		current = millis();
		score += (int)(current - start);
	}
}
