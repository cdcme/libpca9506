#ifndef REGISTERS_LIBRARY_H
#define REGISTERS_LIBRARY_H

#include "libpca9606.h"

#include <inttypes.h>

// Register definitions—pp. 9–10

/** Input port registers */
#define IP_REG 0x00

/** Output port registers */
#define OP_REG 0x08

/** Polarity inversion registers */
#define PI_REG 0x10

/** I/O Configuration registers */
#define IOC_REG 0x18

/** Mask interrupt registers */
#define MSK_BASE 0x20

/** Low-level access to user callback wrappers for initialization */
void i2c_bus_read(pca9606_s *, uint8_t r);
void i2c_bus_write(pca9606_s *, uint8_t r, uint8_t d);

/** Private utilities */
void set_register_byte(pca9606_s *h, uint8_t r, uint8_t n, uint8_t v);
void get_register_byte(pca9606_s *h, uint8_t r, uint8_t n);

/** Convenience to set all pins at once */
void set_register_bytes(pca9606_s *h, uint8_t r, uint8_t v);

#endif

