extern "C" {
	#include "CAN_driver.h"
}

void setup()
{

	Serial.begin(9600);

	if(CAN_init(MCP_MODE_LOOPBACK))
{
		Serial.println("[ERROR] MCP2515 is not in configuration mode after reset!\n");
}	else{
		Serial.println("CAN_init()... OK");
}
	delay(2000);
}

void loop()
{
    
     CanMessage_t message;
     memset(&message, 0, sizeof(CanMessage_t));
     
     message.id = 7;
     message.length = 4;
     message.data[0] = 'A';
     message.data[1] = 'B';
     message.data[2] = 'C';
     message.data[3] = 'D';
     
	
    byte error_code = CAN_send(&message);
	switch(error_code)
	{
		case 1:
			Serial.println("Send has failed !");
			break;
		case 2:
			Serial.println("Send lost arbitration !");
			break;
		case 3:
			Serial.println("Send aborted !");
			break;
		case 4:
			Serial.println("Strange!");
			break;
		case 0:
			Serial.println("Send succeeded !");
			break;
	}
    
	CanMessage_t resp;
	resp = CAN_receive();
	Serial.println("Resp");
    Serial.println(resp.id);
    Serial.println(resp.length);
	int i;
	if(resp.length <= 8) {
		Serial.println("Data");
		for(i = 0; i < resp.length; i++)
		{
			Serial.println(resp.data[i]);
			delay(10);
		}
	}
	delay(10);
}
