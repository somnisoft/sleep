/**
 * @file
 * @brief test seams
 * @author James Humphrey (humphreyj@somnisoft.com)
 *
 * This software has been placed into the public domain using CC0.
 */

#include <limits.h>
#include <unistd.h>

#include "test.h"

/**
 * Error counter for @ref test_seam_sleep.
 */
int g_test_seam_err_ctr_sleep = -1;

/**
 * Control when sleep() fails.
 *
 * @param[in] seconds Number of seconds to sleep the process.
 * @retval    0       The process has slept for @p seconds seconds.
 * @retval    >0      The number of seconds the process did not sleep for.
 */
unsigned
test_seam_sleep(unsigned seconds){
  unsigned unslept;

  if(g_test_seam_err_ctr_sleep == 0){
    unslept = UINT_MAX;
  }
  else{
    unslept = sleep(seconds);
  }
  return unslept;
}

