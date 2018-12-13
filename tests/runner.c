#include "runner.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    struct greatest_report_t report;

    GREATEST_INIT();
    greatest_set_verbosity(3);

    RUN_SUITE(test_driver_init);
    RUN_SUITE(test_register_ops);

    GREATEST_PRINT_REPORT();

    greatest_get_report(&report);

    if(report.failed > 0) return 1;

    return 0;
}
