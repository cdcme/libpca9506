#include "libpca9506.h"
#include "registers.h"

#include <stdio.h>

// A convenience... you could also get the bit from the byte in driver->data
static uint read_bit_from_bank(pca9506_s *h, u8 bank_address, uint bit_position) {
    return get_bit(h, bank_address, bit_position);
}

static void set_bit_in_bank(pca9506_s *h, u8 bank_address, uint bit_position) {
    set_bit(h, bank_address, bit_position);
}

static void clear_bit_in_bank(pca9506_s *h, u8 bank_address, uint bit_position) {
    clear_bit(h, bank_address, bit_position);
}

static void read_bank(pca9506_s *h, u8 bank_address) {
    pca9506_i2c_bus_read(h, bank_address);
}

static void set_bank(pca9506_s *h, u8 bank_address) {
    pca9506_i2c_bus_write(h, bank_address, HIGH);
}

static void clear_bank(pca9506_s *h, u8 bank_address) {
   pca9506_i2c_bus_write(h, bank_address, LOW);
}

pca9506_s pca9506_configure_handle(pca9506_s driver){
    if(!(driver.bus_reader && driver.bus_writer)){
        driver.command = "cb_check";
        driver.status = "Invalid input: bus reader and bus writer callbacks are both required.";
    } else {
        driver.command = "rw_check";

        // Quick & dirty read/write checks; only verifies the interface, should break on the caller's side.
        pca9506_i2c_bus_read(&driver, 0x18);
        pca9506_i2c_bus_write(&driver, 0x18, driver.data);
    }

    driver.read_bit_from_bank = read_bit_from_bank;
    driver.set_bit_in_bank = set_bit_in_bank;
    driver.clear_bit_in_bank = clear_bit_in_bank;
    driver.read_bank = read_bank;
    driver.set_bank = set_bank;
    driver.clear_bank = clear_bank;

    driver.command = driver.command == NULL ? "init" : driver.command;
    driver.status = driver.status == NULL ? "ok" : driver.status;

    return driver;
}

