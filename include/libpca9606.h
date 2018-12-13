/**
 * \file libpca9606.h
 *
 * \brief Driver for the NXP Semiconductors PCA9605/06 40-bit I2C-bus I/O port with RESET, OE and INT
 *
 * \see https://www.nxp.com/docs/en/data-sheet/PCA9505_9506.pdf
 * \see https://github.com/torvalds/linux/blob/master/include/linux/i2c.h#L152
 */

#ifndef LIBPCA9606_LIBRARY_H
#define LIBPCA9606_LIBRARY_H

#include <inttypes.h>

/** Initializes a driver_handle struct with values provided by the user. */
#define pca9606(...) (configure_handle((pca9606_s){__VA_ARGS__}))

/** Primitive data type aliases for readability. */
typedef const char *command, *status;

/** Aggregate types */
struct driver_handle;

/**
 * Types for the I2C bus read and write callbacks.
 * Modeled on the I2C interface for Linux (\c i2c_smbus_read_byte_data, etc.)
 *
 * \see https://github.com/torvalds/linux/blob/master/include/linux/i2c.h#L152
 */
typedef uint8_t (*i2c_bus_read_cb)(struct driver_handle *, uint8_t);
typedef uint8_t (*i2c_bus_write_cb)(struct driver_handle *, uint8_t , uint8_t);

/** Type definition for the driver handle */
typedef struct driver_handle {
    uint8_t data;                  // Data last read/written
    uint8_t address;               // Last register read to/written from
    command command;               // Last command attempted
    status status;                 // Status (ok) or error message
    i2c_bus_read_cb bus_reader;    // I2C Bus reader callback
    i2c_bus_write_cb bus_writer;   // I2C Bus writer callback
} pca9606_s;

/** Private, used by the macro defined above. */
pca9606_s configure_handle(pca9606_s);

#endif
