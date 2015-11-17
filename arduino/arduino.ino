#include "CAN_driver.h"
#include "CAN_test.h"
#include "MCP2515_driver.h"
#include "ir_driver.h"
#include "servo_driver.h"
#include <Wire/Wire.h>
#include "motor_driver.h"
#include "controller_driver.h"
#include <stdio.h>

#define SCORE_TIMEOUT 1000

Controller controller;

int uart_hack(char c, FILE* f)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
    return 1;
}

void setup()
{
    // Drivers initialization
    CAN_init(MCP_MODE_NORMAL);
    ir_init();
    servo_init();
    motor_init();
    controller_calibrate(&controller);

    // Printing over serial port
    Serial.begin(9600);
    fdevopen(uart_hack, NULL);

    printf("Setup... OK!\n");
}

void loop()
{
    // Store incoming messages
    CanMessage_t resp;
    // Keep track of the elapsed time
    uint32_t     last, current;
    uint16_t     score     = 0;
    uint8_t      playing   = 0;
    uint32_t     last_ball = 0;
    uint32_t     count     = 0;

    current = last = millis();

    while (1)
    {
        current = millis();
        last = current;

        // Check for incoming messages
        resp = CAN_receive();
        if (resp.id == INPUT_ID)
        {
            // Servo is controlled by right slider and motor by joystick
            int8_t right_slider = resp.data[3] - 256 / 2;
            servo_joystick_control(right_slider);
            controller_set_reference(&controller, (int8_t) resp.data[1]);
        }
        else if (resp.id == SCORE)
        {
            // Reset score
            score   = 0;
            // Allow the motor to be controlled
            playing = 1;
        }
        else if (resp.id == SETTINGS)
        {
            controller_set_input_coeff(&controller, resp.data[0]);
        }

        // If the player loses
        if (ir_check() == 1)
        {
            // Check if the ball has not been already detected
            if ((millis() - last_ball) > SCORE_TIMEOUT)
            {
                // Send the current score over can
                CanMessage_t message;
                message.id      = SCORE;
                message.length  = 2;
                message.data[0] = score >> 8;
                message.data[1] = score;
                CAN_send(&message);

                // Disable the motor control
                playing = 0;

                // Turn the motor off
                motor_control(0);
            }
            last_ball = millis();
        }

        if (count % 100 == 0)
            score += 1;

        if (playing)
            controller_pi(&controller, (uint32_t) current - last);

        count++;
    }
}
