#ifndef TESTS_H
#define TESTS_H

#include "greatest.h"
#include "theft.h"

#include "libpca9506.h"
#include "registers.h"

typedef struct mock_register {
    u8 address;
    u8 value;
} mock_register_s;

void set_up_mock_driver(pca9506_s *);
void set_up_theft_run_config(struct theft_run_config *);
void set_up_theft_run_config2(struct theft_run_config *);
u8 mock_bus_reader(pca9506_s *, u8 address);
u8 mock_bus_writer(pca9506_s *, u8 address, u8 data_in);

#endif
