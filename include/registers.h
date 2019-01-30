#ifndef PCA9506_REGISTERS_H
#define PCA9506_REGISTERS_H

#include "libpca9506.h"

#include <inttypes.h>

/** Make static functions available for testing */
#ifdef TESTING
#define STATIC
#else
#define STATIC static
#endif

/** Bitwise operations */
#define GET_MASK(n) (1u << (n))                 // Get the bitmask for a given number n
#define GET_BIT(n, b) ((n >> b) & 1u)           // Get the bit at b from number n
#define SET_BIT(n, b) ((n) |= (1u << (b)))      // Set the bit b of number n
#define CLEAR_BIT(n, b) ((n) &= ~(1u << (b)))   // Clear the bit b of number n

/** Format binary for logging/testing, e.g.,
 *  printf("Data in binary: "BYTE_TO_BIN"\n", TO_BINARY(d));
 */
#define BYTE_TO_BIN "%c%c%c%c%c%c%c%c"
#define TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

/** Conveniences */
#define ZERO 0x00
#define OK   ZERO

#define ONE  0x01
#define ERR  ONE

/** Low-level access to user callback wrappers for initialization */
void pca9506_i2c_bus_read(pca9506_s *h, u8 r);
void pca9506_i2c_bus_write(pca9506_s *h, u8 r, u8 d);

/** Private API */

void set_bit(pca9506_s *h, u8 r, uint b);
void clear_bit(pca9506_s *h, u8 r, uint b);
uint get_bit(pca9506_s *h, u8 r, uint b);

#endif

