/**
 * @file
 * @brief test suite
 * @author James Humphrey (humphreyj@somnisoft.com)
 *
 * This software has been placed into the public domain using CC0.
 */

#include <sys/wait.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "test.h"

/**
 * Call @ref sleep_main with the given arguments.
 *
 * @param[in] time_str           See @ref sleep_main.
 * @param[in] extra_arg          Add a second invalid argument.
 * @param[in] expect_exit_status Expected exit status code.
 */
static void
test_sleep_main(const char *const time_str,
                const char *const extra_arg,
                const int expect_exit_status){
  int argc;
  char *argv[3];
  int status;
  int exit_status;
  pid_t pid;
  size_t i;

  for(i = 0; i < 3; i++){
    argv[i] = malloc(100);
    assert(argv[i]);
  }
  argc = 0;
  strcpy(argv[argc++], "sleep");
  if(time_str){
    strcpy(argv[argc++], time_str);
  }
  if(extra_arg){
    strcpy(argv[argc++], extra_arg);
  }
  pid = fork();
  assert(pid >= 0);
  if(pid == 0){
    exit_status = sleep_main(argc, argv);
    exit(exit_status);
  }
  assert(waitpid(pid, &status, 0) == pid);
  assert(WIFEXITED(status));
  assert(WEXITSTATUS(status) == expect_exit_status);
  for(i = 0; i < 3; i++){
    free(argv[i]);
  }
}

/**
 * Convert an unsigned long to a string.
 *
 * @param[in] ul Unsigned long value to convert to a string.
 * @return       Pointer to converted string located in static memory.
 */
static const char *
test_conv_ul_to_str(const unsigned long ul){
  static char conv_str[1000];
  int nbytes_written;

  nbytes_written = sprintf(conv_str, "%lu", ul);
  assert(nbytes_written > 0);
  return conv_str;
}

/**
 * Run all test cases for the sleep utility.
 */
static void
test_all(void){
  /* No arguments. */
  test_sleep_main(NULL, NULL, EXIT_FAILURE);

  /* Extra argument. */
  test_sleep_main("1", "invalid", EXIT_FAILURE);

  /* Blank time argument. */
  test_sleep_main("", NULL, EXIT_FAILURE);

  /* Invalid character at beginning of time string. */
  test_sleep_main("x1", NULL, EXIT_FAILURE);

  /* Invalid character at end of time string. */
  test_sleep_main("1x", NULL, EXIT_FAILURE);

  /* Exactly ULONG_MAX. */
  g_test_seam_err_ctr_sleep = 0;
  test_sleep_main(test_conv_ul_to_str((unsigned long)ULONG_MAX),
                  NULL,
                  EXIT_SUCCESS);
  g_test_seam_err_ctr_sleep = -1;

  /* Large value within range of (UINT_MAX, ULONG_MAX). */
  g_test_seam_err_ctr_sleep = 0;
  test_sleep_main(test_conv_ul_to_str((unsigned long)UINT_MAX + 1),
                  NULL,
                  EXIT_SUCCESS);
  g_test_seam_err_ctr_sleep = -1;

  /* Larger than ULONG_MAX. */
  test_sleep_main("9999999999999999999999999999999999999999999999999999999999",
                  NULL,
                  EXIT_FAILURE);

  /*
   * Set errno to ERANGE to cover the scenario where that has been
   * set but the value does not exceed the range.
   */
  errno = ERANGE;
  test_sleep_main("0",
                  NULL,
                  EXIT_SUCCESS);

  /* Successfully sleep for 0 seconds. */
  test_sleep_main("0",
                  NULL,
                  EXIT_SUCCESS);

  /* Successfully sleep for 1 second. */
  test_sleep_main("1",
                  NULL,
                  EXIT_SUCCESS);

  /* Successfully sleep for 2 seconds. */
  test_sleep_main("2",
                  NULL,
                  EXIT_SUCCESS);
}

/**
 * Test sleep utility.
 *
 * Usage: test
 *
 * @retval 0 All tests passed.
 */
int
main(void){
  test_all();
  return 0;
}

