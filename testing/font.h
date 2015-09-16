/*
 * font.h
 *
 * Created: 16.09.2015 13:15:17
 *  Author: vegasten
 */ 


#ifndef FONT_H_
#define FONT_H_

#define FONT_WIDTH 5

#include <avr/pgmspace.h>

const unsigned char font_5[95][5];

const unsigned char* get_char(char c);


#endif /* FONT_H_ */