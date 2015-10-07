extern "C" {
	#include "CAN_driver.h"
}

void setup()
{

  Serial.begin(9600);
  CAN_init(MCP_MODE_NORMAL);
  Serial.println("CAN_init()... OK");
  delay(2000);
}

void loop()
{
    CanMessage_t resp;
//     CanMessage_t resp;
//     memset(&message, 0, sizeof(CanMessage_t));
//     
//     message.id = 15;
//     message.length = 5;
//     message.data[0] = 'T';
//     message.data[1] = 'E';
//     message.data[2] = 'S';
//     message.data[3] = 'T';
//     
//     CAN_send(&message);
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
