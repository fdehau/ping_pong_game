/*
 * util.h
 *
 * Created: 09.09.2015 12:39:45
 *  Author: vegasten
 */


#ifndef UTIL_H_
#define UTIL_H_

#define bit_get(p, m) ((p) & (m))
#define bit_set(p, m) ((p) |= (m))
#define bit_clear(p, m) ((p) &= ~(m))
#define bit_flip(p, m) ((p) ^= (m))
#define bit_write(c, p, m) (c ? bit_set(p, m) : bit_clear(p, m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))




#endif /* UTIL_H_ */