/*
 * CAN_test.h
 *
 * Created: 21.10.2015 13:00:31
 *  Author: vegasten
 */


#ifndef CAN_TEST_H_
#define CAN_TEST_H_

#include "CAN_driver.h"
#define F_CPU 4915200
#include <util/delay.h>
#include <Arduino.h>
#include <HardwareSerial.h>

void CAN_test_loopback();
void CAN_test_normal_send();
void CAN_test_normal_receive();

#endif /* CAN_TEST_H_ */