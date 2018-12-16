#include "registers.h"

/** Userland I2C bus read/write callback wrappers */

void pca9506_i2c_bus_read(pca9506_s *h, u8 r) {
    u8 result = h->bus_reader(h, r);
    h->command = "i2c_read";
    h->status = "ok";
    h->address = r;
    h->data = result;
}

void pca9506_i2c_bus_write(pca9506_s *h, u8 r, u8 d) {
    u8 result = h->bus_writer(h, r, d);
    h->command = "i2c_write";
    h->status = result == 0 ? "ok" : "error";
    h->address = r;
    h->data = d;
}

void set_bit(pca9506_s *h, u8 r, uint b) {
    pca9506_i2c_bus_read(h, r);
    pca9506_i2c_bus_write(h, r, SET_BIT(h->data, b));
}

void clear_bit(pca9506_s *h, u8 r, uint b) {
    pca9506_i2c_bus_read(h, r);
    pca9506_i2c_bus_write(h, r, CLEAR_BIT(h->data, b));
}

uint get_bit(pca9506_s *h, u8 r, uint b) {
    pca9506_i2c_bus_read(h, r);
    return GET_BIT(h->data, b);
}

