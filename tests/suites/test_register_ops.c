#include "tests.h"

/* Test setup begin */

static pca9506_s mock_driver;
static struct theft_run_config run_config, run_config2;

static void setup_cb(void *data) {
    (void)data;

    set_up_mock_driver(&mock_driver);
    set_up_theft_run_config(&run_config);
    set_up_theft_run_config2(&run_config2);
}

/* Test setup ends here; tests begin */
static enum theft_trial_res
property_can_set_bank_bits(struct theft *t, void *arg1) {
    (void)t;

    u8 mock_register = *(u8 *)arg1;
    mock_driver.set_bank(&mock_driver, mock_register);

    ASSERT_EQ(mock_driver.address, mock_register);
    ASSERT_EQ(mock_driver.data, HIGH);

    return THEFT_TRIAL_PASS;
}

static enum theft_trial_res
property_can_clear_bank_bits(struct theft *t, void *arg1) {
    (void)t;

    u8 mock_register = *(u8 *)arg1;
    mock_driver.clear_bank(&mock_driver, mock_register);

    ASSERT_EQ(mock_driver.address, mock_register);
    ASSERT_EQ(mock_driver.data, LOW);

    return THEFT_TRIAL_PASS;
}

static enum theft_trial_res
property_can_read_bit_from_bank(struct theft *t, void *arg1, void *arg2) {
    (void)t;

    u8 mock_register = *(u8 *)arg1;
    uint mock_position = *(uint *)arg2;

    uint result = mock_driver.read_bit_from_bank(&mock_driver, mock_register, mock_position);
    ASSERT_EQ(result, 0);

    return THEFT_TRIAL_PASS;
}

static enum theft_trial_res
property_can_set_bit_in_bank(struct theft *t, void *arg1, void *arg2) {
    (void)t;

    u8 mock_register = *(u8 *)arg1;
    uint mock_position = *(uint *)arg2;

    uint result = mock_driver.read_bit_from_bank(&mock_driver, mock_register, mock_position);
    ASSERT_EQ(result, 0);

    mock_driver.set_bit_in_bank(&mock_driver, mock_register, 3);
    result = mock_driver.read_bit_from_bank(&mock_driver, mock_register, 3);
    ASSERT_EQ(result, 1);

    return THEFT_TRIAL_PASS;
}

static enum theft_trial_res
property_can_clear_bit_in_bank(struct theft *t, void *arg1, void *arg2) {
    (void)t;

    u8 mock_register = *(u8 *)arg1;
    uint mock_position = *(uint *)arg2;

    uint result = mock_driver.read_bit_from_bank(&mock_driver, mock_register, mock_position);
    ASSERT_EQ(result, 0);

    mock_driver.set_bit_in_bank(&mock_driver, mock_register, 3);
    result = mock_driver.read_bit_from_bank(&mock_driver, mock_register, 3);
    ASSERT_EQ(result, 1);

    mock_driver.clear_bit_in_bank(&mock_driver, mock_register, 3);
    result = mock_driver.read_bit_from_bank(&mock_driver, mock_register, 3);
    ASSERT_EQ(result, 0);

    return THEFT_TRIAL_PASS;
}

TEST expect_setting_bank_high_to_succeed(void) {
    enum theft_run_res res;

    run_config.name = __func__;
    run_config.prop1 = property_can_set_bank_bits;

    res = theft_run(&run_config);

    ASSERT_EQ(res, THEFT_RUN_PASS);

    PASS();
}

TEST expect_setting_bank_low_to_succeed(void) {
    enum theft_run_res res;

    run_config.name = __func__;
    run_config.prop1 = property_can_clear_bank_bits;

    res = theft_run(&run_config);

    ASSERT_EQ(res, THEFT_RUN_PASS);

    PASS();
}

TEST expect_getting_bit_to_succeed(void) {
    enum theft_run_res res;

    run_config2.name = __func__;
    run_config2.prop2 = property_can_read_bit_from_bank;

    res = theft_run(&run_config2);

    ASSERT_EQ(res, THEFT_RUN_PASS);

    PASS();
}

TEST expect_setting_bit_to_succeed(void) {
    enum theft_run_res res;

    run_config2.name = __func__;
    run_config2.prop2 = property_can_set_bit_in_bank;

    res = theft_run(&run_config2);

    ASSERT_EQ(res, THEFT_RUN_PASS);

    PASS();
}

TEST expect_clearing_bit_to_succeed(void) {
    enum theft_run_res res;

    run_config2.name = __func__;
    run_config2.prop2 = property_can_clear_bit_in_bank;

    res = theft_run(&run_config2);

    ASSERT_EQ(res, THEFT_RUN_PASS);

    PASS();
}

SUITE(test_register_ops) {
    SET_SETUP(setup_cb, NULL);

    RUN_TEST(expect_setting_bank_high_to_succeed);
    RUN_TEST(expect_setting_bank_low_to_succeed);
    RUN_TEST(expect_getting_bit_to_succeed);
    RUN_TEST(expect_setting_bit_to_succeed);
    RUN_TEST(expect_clearing_bit_to_succeed);
}
