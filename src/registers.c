#include "registers.h"

/** Userland I2C bus read/write callback wrappers */

void pca9506_i2c_bus_read(pca9506_s *h, uint8_t r) {
    uint8_t result = h->bus_reader(h, r);
    h->command = "i2c_read";
    h->status = "ok";
    h->address = r;
    h->data = result;
}

void pca9506_i2c_bus_write(pca9506_s *h, uint8_t r, uint8_t d) {
    uint8_t result = h->bus_writer(h, r, d);
    h->command = "i2c_write";
    h->status = result == 0 ? "ok" : "error";
    h->address = r;
    h->data = d;
}

void set_register_byte(pca9506_s *h, uint8_t r, uint8_t n, uint8_t v){
    pca9506_i2c_bus_write(h, r + n, v);
}

void get_register_byte(pca9506_s *h, uint8_t r, uint8_t n){
    pca9506_i2c_bus_read(h, r + n);
}

void set_register_bytes(pca9506_s *h, uint8_t r, uint8_t v) {
    pca9506_i2c_bus_write(h, r, v);
    pca9506_i2c_bus_write(h, r + (uint8_t) 1, v);
    pca9506_i2c_bus_write(h, r + (uint8_t) 2, v);
    pca9506_i2c_bus_write(h, r + (uint8_t) 3, v);
    pca9506_i2c_bus_write(h, r + (uint8_t) 4, v);
}
