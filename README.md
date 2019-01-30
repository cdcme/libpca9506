# libpca9506

C driver for the NXP Semiconductors PCA9506/06 40-bit I2C-bus I/O port with RESET, OE and INT ([datasheet](https://github.com/minnowpod/libpca9506/tree/master/docs/PCA9506_06.pdf))

## Features

- Tests with [greatest](https://github.com/silentbicycle/greatest) and [theft](https://github.com/silentbicycle/theft)
- Bring your own I2C and hardware interface libraries
- Minimal dependencies

## Goals

- Strict, full implementation of manufacturer specifications
- A clean, user-friendly interface for application developers and library writers
- No tight coupling to a specific I2C library or hardware platform (Linux I2C, various Pi/Arduino libraries, etc.)
- No tight coupling to a specific application (LEDs vs. servos, etc.)
- Modern C (C11) development practices, like unit tests, property-based tests, [modern CMake (3.13)](https://cliutils.gitlab.io/modern-cmake/), etc.

## Installation

The simplest way to install the library into your own CMake project at the moment is to add it as a git submodule like this:

```shell
// clone the repo
$ git clone git@github.com:minnowpod/libpca9506.git && cd libpca9506

// check out the most recent tag to a branch
$ git checkout tags/v0.2.0 -b v0.2.0

// in your project, add it as a submodule
$ git submodule add -b v0.2.0 ../../../libpca9506 vendor/libpca9506
```

## Usage

Example application code might look something like this:

```C
#include "libpca9506.h"

// Application (not library) dependencies
#include "pigpio.h"
#include <zconf.h>

#define I2C_BUS 1
#define I2C_BUS_ADDRESS 0x40
#define I2C_FLAGS 0

// ALL management of the I2C bus itself is your application's responsibility!
static int pi, handle;

// Set up an I2C reader callback
static uint8_t i2c_read_byte_cb(pca9506_s *driver, uint8_t r) {
    // This is pigpio's function we're wrapping here, but it could be any other library, as well
    int result = i2c_read_byte_data(pi, (uint8_t)servo_master_handle, r);

    // You can add information to the driver struct's status field if you like
    driver->status = (result >= 0) ? "ok" : pigpio_error(result);

    return (uint8_t)result;
}

static uint8_t i2c_write_byte_cb(pca9506_s *driver, uint8_t r, uint8_t d) {
    // This is pigpio's function we're wrapping here, but it could be any other library, as well
    int result = i2c_write_byte_data(pi, (uint8_t)servo_master_handle, r, d);

    // You can add information to the driver struct's status field if you like
    driver->status = (result >= 0) ? "ok" : pigpio_error(result);

    return (uint8_t)result;
}

int main(int argc, char **argv) {
    pi = pigpio_start(NULL, NULL);
    char *pi_status = (pi >= 0) ? "ok" : pigpio_error(pi);

    handle = i2c_open(pi, I2C_BUS, I2C_BUS_ADDRESS, I2C_FLAGS);
    char *handle_status = (handle >= 0) ? "ok" : pigpio_error(handle);

    printf("\nMain\n====\n: %d");
    printf("\nPIGPIO Status: %s", pi_status);
    printf("\nI2C Handle Status: %s\n", handle_status);
    printf("Initializing driver...");

    // Initialize your driver struct—also does test read and write operations
    pca9506_s my_driver = pca9506(.bus_reader=bus_byte_reader, .bus_writer=bus_byte_writer);

    printf("%s\n", my_driver.status);

    // set outputs
    my_driver.clear_bank(&my_driver, IOC0);
    my_driver.clear_bank(&my_driver, IOC1);
    my_driver.clear_bank(&my_driver, IOC2);
    my_driver.clear_bank(&my_driver, IOC3);
    my_driver.clear_bank(&my_driver, IOC4);

    // read some data from IP0
    my_driver.read_bank(&my_driver, IP0);

    // set 3rd bit in OP3
    my_driver.set_bit_in_bank(&my_driver, OP3, 2);

    // etc..

    // pigpio-specific...
    int close = i2c_close(pi, (uint)handle);
    char *close_message = (close == PI_BAD_HANDLE) ? "PI_BAD_HANDLE" : "CLOSED";
    printf("\nClose result: %s\n", close_message);

    pigpio_stop(pi);

    if(close == PI_BAD_HANDLE) return 1;

    return 0;
}
```

See also the included [examples](https://github.com/minnowpod/libpca9506/tree/master/examples).

## Who maintains this library?

This library is maintained by [Minnow](https://minnow.me/), an IoT startup that makes smart food pickup kiosks called pods.

## How do I contribute?

Contributions are welcome! Check out [CONTRIBUTING](https://github.com/minnowpod/libpca9506/tree/master/CONTRIBUTING.md) for instructions.

## How is this library versioned?

This library follows the principles of [Semantic Versioning](http://semver.org/). You can find each new release,
along with the changelog, in the [CHANGELOG](https://github.com/minnowpod/libpca9506/tree/master/CHANGELOG.md).

During initial development, the major version will be 0 (e.g., `0.x.y`), which indicates the code does not yet have a
stable API. Once we hit `1.0.0`, we will make every effort to maintain a backwards compatible API and use the MAJOR,
MINOR, and PATCH versions on each release to indicate any incompatibilities.

## License

This code is released under the MIT License. Please see [LICENSE](https://github.com/minnowpod/libpca9506/tree/master/LICENSE) for more details.

