#include "CAN_driver.h"
#include "CAN_test.h"
#include "MCP2515_driver.h"
#include "servo_driver.h"


void setup()
{
	Serial.begin(9600);
	servo_init();
	//CAN_test_normal_receive();
	//delay(2000);
}

void loop()
{
	//analogWrite(3,50);
	delay(200);
	
}
