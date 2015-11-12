#include "CAN_driver.h"
#include "CAN_test.h"
#include "MCP2515_driver.h"
#include "ir_driver.h"
#include "servo_driver.h"
#include <Wire/Wire.h>
#include "motor_driver.h"
#include "controller_driver.h"
#include <stdio.h>

unsigned long start, last, current;
uint32_t      score = 0;

Controller controller;
int16_t    encoder_state;

int uart_hack(char c, FILE* f)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
    return 1;
}

//static FILE* f = FDEV_SETUP_STREAM(uart_hack, NULL, _FDEV_SETUP_READ);

void setup()
{
    CAN_init(MCP_MODE_NORMAL);

    ir_init();
    servo_init();
    motor_init();
    controller_calibrate(&controller);

    start = last = current = millis();

    Serial.begin(9600);
    fdevopen(uart_hack, NULL);
}
#define SCORE_TIMEOUT 1000

void loop()
{
    CanMessage_t resp;

    uint32_t last_ball = 0;

    while (1)
    {
        last    = current;
        current = millis() - start;

        resp = CAN_receive();
        if (resp.id == INPUT_ID)
        {
            servo_joystick_control((int8_t) resp.data[1]);
            motor_control((int8_t) resp.data[1]);
            uint8_t left_slider = resp.data[3];
            //controller_set_reference(&controller, left_slider);
            //CAN_print_message(&resp);
        }

        if (ir_check() == 1)
        {
            Serial.println(millis() - last_ball);
            if ((millis() - last_ball) > SCORE_TIMEOUT)
            {
                CanMessage_t message;
                message.id      = SCORE;
                message.length  = 2;
                message.data[0] = score >> 8;
                message.data[1] = score;
                CAN_send(&message);
                Serial.print("Score updated: ");
                Serial.println(score);
                score = 0;
            }
            last_ball = millis();
        }
        score += (int)(current - last);

        controller_pi(&controller, (int) current - last);
    }
}
