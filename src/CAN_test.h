/**
 * @file CAN_test.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Test suite for the CAN protocol
 */

#ifndef CAN_TEST_H_
#define CAN_TEST_H_

#include "CAN_driver.h"
#include "util.h"

void CAN_test_loopback();
void CAN_test_normal_send();
void CAN_test_normal_receive();

#endif /* CAN_TEST_H_ */