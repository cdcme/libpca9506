/**
 * \file libpca9606.h
 *
 * \brief Driver for the NXP Semiconductors PCA9605/06 40-bit I2C-bus I/O port with RESET, OE and INT
 *
 * \see https://www.nxp.com/docs/en/data-sheet/PCA9505_9506.pdf
 * \see https://github.com/torvalds/linux/blob/master/include/linux/i2c.h#L152
 */

#ifndef PCA9606_LIBRARY_H
#define PCA9606_LIBRARY_H

#include <inttypes.h>

/** Initializes a driver_handle struct with values provided by the user. */
#define pca9606(...) (pca9606_configure_handle((pca9606_s){__VA_ARGS__}))

/** Primitive data type aliases for readability. */
typedef const char *command, *status;

/** Aggregate types */
struct pca9606_driver_handle;

/**
 * Types for the I2C bus read and write callbacks.
 * Modeled on the I2C interface for Linux (\c i2c_smbus_read_byte_data, etc.)
 *
 * \see https://github.com/torvalds/linux/blob/master/include/linux/i2c.h#L152
 */
typedef uint8_t (*pca9606_i2c_bus_read_cb)(struct pca9606_driver_handle *, uint8_t);
typedef uint8_t (*pca9606_i2c_bus_write_cb)(struct pca9606_driver_handle *, uint8_t , uint8_t);

/** Type definition for the driver handle */
typedef struct pca9606_driver_handle {
    uint8_t data;                  // Data last read/written
    uint8_t address;               // Last register read to/written from
    command command;               // Last command attempted
    status status;                 // Status (ok) or error message
    pca9606_i2c_bus_read_cb bus_reader;    // I2C Bus reader callback
    pca9606_i2c_bus_write_cb bus_writer;   // I2C Bus writer callback
} pca9606_s;

/** Private, used by the macro defined above. */
pca9606_s pca9606_configure_handle(pca9606_s);

/** Public API */

/** Set the given pin as an I/O output */
void set_as_output(pca9606_s *h, int pin);

/** Set the given pin as an I/O input */
void set_as_input(pca9606_s *h, int pin);

/** Set all pins as I/O outputs */
void set_as_outputs(pca9606_s *h);

/** Set all pins as I/O inputs */
void set_as_inputs(pca9606_s *h);

/** Read I/O data */
void io_read(pca9606_s *h, int pin);

/** Write I/O data */
void io_write(pca9606_s *h, int pin, uint8_t value);

/** Set output pins high */
void set_high(pca9606_s *h);

/** Set output pins low */
void set_low(pca9606_s *h);

#endif
