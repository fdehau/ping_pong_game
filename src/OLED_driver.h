/**
 * @file OLED_driver.h
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Drawing functions to interact with the OLED display
 */

#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "font.h"

void OLED_init();
void OLED_clr();
void OLED_write_command(unsigned char cmd);
void OLED_pos(int page, int column, int width);
void OLED_print(char* string);
void OLED_clear_line(int line);
void OLED_goto_line(int line);
void OLED_print_arrow(int row, int col);

#endif /* OLED_DRIVER_H_ */