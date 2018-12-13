#include "tests.h"

#include <stdint.h>

mock_register_s mockr;

void set_up_mock_driver(pca9606_s *driver) {
    *driver = pca9606(.bus_reader=mock_bus_reader, .bus_writer=mock_bus_writer);
}

void set_up_theft_run_config(struct theft_run_config *config) {
    theft_seed seed = theft_seed_of_time();

    *config = (struct theft_run_config){
        .type_info = {
            theft_get_builtin_type_info(THEFT_BUILTIN_uint8_t)
        },
        .seed = seed,
        .trials = 100
    };
}

uint8_t mock_bus_reader(pca9606_s *driver, uint8_t address) {
    (void)driver;

    mockr.address = address;
    return mockr.value;
}

uint8_t mock_bus_writer(pca9606_s *driver, uint8_t address, uint8_t data_in) {
    (void)driver;

    mockr.address = address;
    mockr.value = data_in;

    return 0;
}

