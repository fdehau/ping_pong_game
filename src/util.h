/**
 * @file util.h
 * @author Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Contains some macros for bits manipulation
 */

#ifndef UTIL_H_
#define UTIL_H_

#define F_CPU 4915200
#include <util/delay.h>
#include <stdlib.h>

#define bit_get(p, m) ((p) & (m))
#define bit_set(p, m) ((p) |= (m))
#define bit_clear(p, m) ((p) &= ~(m))
#define bit_flip(p, m) ((p) ^= (m))
#define bit_write(c, p, m) (c ? bit_set(p, m) : bit_clear(p, m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))

#endif /* UTIL_H_ */
