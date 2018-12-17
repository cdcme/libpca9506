#include "libpca9606.h"
#include "registers.h"

#include <stdio.h>

pca9606_s pca9606_configure_handle(pca9606_s driver){
    if(!(driver.bus_reader && driver.bus_writer)){
        driver.command = "cb_check";
        driver.status = "Invalid input: bus reader and bus writer callbacks are both required.";
    } else {
        driver.command = "rw_check";

        // Quick & dirty read/write checks; only verifies the interface, should break on the caller's side.
        pca9606_i2c_bus_read(&driver, 0x18);
        pca9606_i2c_bus_write(&driver, 0x18, driver.data);
    }

    driver.command = driver.command == NULL ? "init" : driver.command;
    driver.status = driver.status == NULL ? "ok" : driver.status;

    return driver;
}

/** Get/set I/O mode for the given pin(s) */

void set_as_output(pca9606_s *h, int p) {
    set_register_byte(h, IOC_REG, (uint8_t)p, 0xFF);
}

void set_as_input(pca9606_s *h, int p) {
    set_register_byte(h, IOC_REG, (uint8_t)p, 0x00);
}

void set_as_outputs(pca9606_s *h) {
    set_register_bytes(h, IOC_REG, 0xFF);
}

void set_as_inputs(pca9606_s *h) {
    set_register_bytes(h, IOC_REG, 0x00);
}

void io_read(pca9606_s *h, int p) {
    get_register_byte(h, IP_REG, (uint8_t)p);
}

void io_write(pca9606_s *h, int p, uint8_t v) {
    set_register_byte(h, OP_REG, (uint8_t)p, v);
}

void set_high(pca9606_s *h) {
    set_register_bytes(h, OP_REG, 0xFF);
}

void set_low(pca9606_s *h) {
    set_register_bytes(h, OP_REG, 0x00);
}

