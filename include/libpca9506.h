/**
 * \file libpca9506.h
 *
 * \brief Driver for the NXP Semiconductors PCA9605/06 40-bit I2C-bus I/O port with RESET, OE and INT
 *
 * \see https://www.nxp.com/docs/en/data-sheet/PCA9505_9506.pdf
 * \see https://github.com/torvalds/linux/blob/master/include/linux/i2c.h#L152
 */

#ifndef PCA9506_LIBRARY_H
#define PCA9506_LIBRARY_H

#include <inttypes.h>

// Register definitions—pp. 9–10

/** Input port registers */
#define IP0 0x00
#define IP1 0x01
#define IP2 0x02
#define IP3 0x03
#define IP4 0x04

/** Output port registers */
#define OP0 0x08
#define OP1 0x09
#define OP2 0x0A
#define OP3 0x0B
#define OP4 0x0C

/** Polarity inversion registers */
#define PI0 0x10
#define PI1 0x11
#define PI2 0x12
#define PI3 0x13
#define PI4 0x14

/** I/O Configuration registers */
#define IOC0 0x18
#define IOC1 0x19
#define IOC2 0x1A
#define IOC3 0x1B
#define IOC4 0x1C

/** Mask interrupt registers */
#define MSK0 0x20
#define MSK1 0x21
#define MSK2 0x22
#define MSK3 0x23
#define MSK4 0x24

/** Bit positions—last 3 bits are reserved */
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4

/** Bit values */

#define HIGH 0xFF
#define LOW  0x00

/** Initializes a driver_handle struct with values provided by the user. */
#define pca9506(...) (pca9506_configure_handle((pca9506_s){__VA_ARGS__}))

/** Primitive data type aliases for readability/conciseness */
typedef char *string;
typedef uint8_t u8;
typedef unsigned int uint;

/** Aggregate types */

struct pca9506_driver;

/**
 * Types for the I2C bus read and write callbacks.
 * Modeled on the I2C interface for Linux (\c i2c_smbus_read_byte_data, etc.)
 *
 * \see https://github.com/torvalds/linux/blob/master/include/linux/i2c.h#L152
 */
typedef u8 (*pca9506_i2c_bus_read_cb)(struct pca9506_driver *driver, u8 address);
typedef u8 (*pca9506_i2c_bus_write_cb)(struct pca9506_driver *driver, u8 address, u8 data);

/** Public API function signatures */
typedef void (*pca9506_fn)(struct pca9506_driver *driver);
typedef uint (*pca9506_bit_read)(struct pca9506_driver *driver, u8 bank_address, uint bit_position);
typedef void (*pca9506_bit_op)(struct pca9506_driver *driver, u8 bank_address, uint bit_position);
typedef void (*pca9506_bank_op)(struct pca9506_driver *driver, u8 bank_address);

/** Type definition for the driver handle */
typedef struct pca9506_driver {
    u8 data;                                // Data last read/written
    u8 address;                             // Last register read to/written from
    string command;                         // Last command attempted
    string status;                          // Status (ok) or error message
    pca9506_i2c_bus_read_cb bus_reader;     // I2C Bus reader callback
    pca9506_i2c_bus_write_cb bus_writer;    // I2C Bus writer callback
    pca9506_bit_read read_bit_from_bank;    // Read the bit value at position p from bank b
    pca9506_bit_op set_bit_in_bank;         // Set the bit (1) at position p in bank b
    pca9506_bit_op clear_bit_in_bank;       // Clear the bit (0) at position p in bank b
    pca9506_bank_op read_bank;              // Read byte data from bank into handle.data
    pca9506_bank_op set_bank;               // Set ALL bits (1) in bank
    pca9506_bank_op clear_bank;             // Clear ALL bits (0) in bank
} pca9506_s;

/** Private, used by the macro defined above. */
pca9506_s pca9506_configure_handle(pca9506_s);

#endif
