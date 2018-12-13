#include "libpca9606.h"
#include "registers.h"

#include <stdio.h>

pca9606_s configure_handle(pca9606_s driver){
    if(!(driver.bus_reader && driver.bus_writer)){
        driver.command = "cb_check";
        driver.status = "Invalid input: bus reader and bus writer callbacks are both required.";
    } else {
        driver.command = "rw_check";

        // Quick & dirty read/write checks; only verifies the interface, should break on the caller's side.
        i2c_bus_read(&driver, 0x00);
        i2c_bus_write(&driver, 0x00, driver.data);
    }

    driver.command = driver.command == NULL ? "init" : driver.command;
    driver.status = driver.status == NULL ? "ok" : driver.status;

    return driver;
}

