#include "tests.h"

static pca9606_s mock_driver;

static void setup_cb(void *data) {
    (void) data;

    set_up_mock_driver(&mock_driver);
}

TEST expect_data_to_be_zero(void) {
    ASSERT_EQ(mock_driver.data, 0);

    PASS();
}

TEST expect_callbacks_to_be_present(void) {
    ASSERT(mock_driver.bus_reader && mock_driver.bus_writer);

    PASS();
}

TEST expect_callback_identities(void) {
    ASSERT_EQ(mock_driver.bus_reader, mock_bus_reader);
    ASSERT_EQ(mock_driver.bus_writer, mock_bus_writer);
    PASS();
}

TEST expect_verifies_callbacks(void) {
    pca9606_s mock_d = pca9606();
    ASSERT_FALSE(mock_d.bus_reader && mock_d.bus_writer);
    ASSERT(mock_d.status != (char *) "ok");
    ASSERT_STR_EQ(mock_d.command, "cb_check");

    PASS();
}

TEST expect_command_to_be_i2c_write(void) {
    ASSERT_STR_EQ(mock_driver.command, "i2c_write");

    PASS();
}

TEST expect_status_to_be_ok(void) {
    ASSERT_STR_EQ(mock_driver.status, "ok");

    PASS();
}

SUITE (test_driver_init) {
    SET_SETUP(setup_cb, NULL);

    RUN_TEST(expect_data_to_be_zero);
    RUN_TEST(expect_callbacks_to_be_present);
    RUN_TEST(expect_callback_identities);
    RUN_TEST(expect_verifies_callbacks);
    RUN_TEST(expect_command_to_be_i2c_write);
    RUN_TEST(expect_status_to_be_ok);
}
