/**
 * @file
 * @brief test seams
 * @author James Humphrey (humphreyj@somnisoft.com)
 *
 * This software has been placed into the public domain using CC0.
 */
#ifndef SLEEP_TEST_SEAMS_H
#define SLEEP_TEST_SEAMS_H

#include "test.h"

/*
 * Redefine these functions to internal test seams.
 */
#undef sleep

/**
 * Inject a test seam to replace sleep.
 */
#define sleep test_seam_sleep

#endif /* SLEEP_TEST_SEAMS_H */

