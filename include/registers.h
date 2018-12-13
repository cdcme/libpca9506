#ifndef REGISTERS_LIBRARY_H
#define REGISTERS_LIBRARY_H

#include "libpca9606.h"

/** Low-level access to user callback wrappers for initialization */
void i2c_bus_read(pca9606_s *, uint8_t r);
void i2c_bus_write(pca9606_s *, uint8_t r, uint8_t d);

#endif

