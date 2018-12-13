#include "registers.h"

/** Userland I2C bus read/write callback wrappers */

void i2c_bus_read(pca9606_s *h, uint8_t r) {
    uint8_t result = h->bus_reader(h, r);
    h->command = "i2c_read";
    h->status = "ok";
    h->address = r;
    h->data = result;
}

void i2c_bus_write(pca9606_s *h, uint8_t r, uint8_t d) {
    uint8_t result = h->bus_writer(h, r, d);
    h->command = "i2c_write";
    h->status = result == 0 ? "ok" : "error";
    h->address = r;
    h->data = d;
}

