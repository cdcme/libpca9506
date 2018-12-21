#include "tests.h"

/* Test setup begin */

static pca9506_s mock_driver;
static struct theft_run_config run_config;

static void setup_cb(void *data) {
    (void)data;

    set_up_mock_driver(&mock_driver);
    set_up_theft_run_config(&run_config);
}

/* Test setup ends here; tests begin */

TEST expect_pass(void) {
    SKIP();
}

SUITE(test_register_ops) {
    SET_SETUP(setup_cb, NULL);

    RUN_TEST(expect_pass);
}
