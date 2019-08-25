/**
 * @file
 * @brief test suite
 * @author James Humphrey (humphreyj@somnisoft.com)
 *
 * This software has been placed into the public domain using CC0.
 */
#ifndef SLEEP_TEST_H
#define SLEEP_TEST_H

int
sleep_main(int argc,
           char *argv[]);

unsigned
test_seam_sleep(unsigned seconds);

extern int g_test_seam_err_ctr_sleep;

#endif /* SLEEP_TEST_H */

