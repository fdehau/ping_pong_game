/**
 * @file font.h
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Font characters and util function to access them
 */

#ifndef FONT_H_
#define FONT_H_

#define FONT_WIDTH 5

#include <avr/pgmspace.h>

const unsigned char font_5[95][5];

const unsigned char * get_char(char c);


#endif /* FONT_H_ */
