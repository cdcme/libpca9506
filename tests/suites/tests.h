#ifndef TESTS_H
#define TESTS_H

#include "greatest.h"
#include "theft.h"

#include "libpca9606.h"
#include "registers.h"

typedef struct mock_register {
    uint8_t address;
    uint8_t value;
} mock_register_s;

void set_up_mock_driver(pca9606_s *);
void set_up_theft_run_config(struct theft_run_config *);
uint8_t mock_bus_reader(pca9606_s *, uint8_t address);
uint8_t mock_bus_writer(pca9606_s *, uint8_t address, uint8_t data_in);

#endif
