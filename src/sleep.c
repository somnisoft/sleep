/**
 * @file
 * @brief sleep utility
 * @author James Humphrey (humphreyj@somnisoft.com)
 *
 * This software has been placed into the public domain using CC0.
 */

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef TEST
/**
 * Declare some functions with extern linkage, allowing the test suite to call
 * those functions.
 */
# define LINKAGE extern
# include "../test/seams.h"
#else /* !(TEST) */
/**
 * Define all functions as static when not testing.
 */
# define LINKAGE static
#endif /* TEST */

/**
 * Main program entry point for sleep utility.
 *
 * Usage:
 * sleep time
 *
 * @param[in]     argc         Number of arguments in @p argv.
 * @param[in,out] argv         Argument list.
 * @retval        EXIT_SUCCESS Successful.
 * @retval        EXIT_FAILURE Error occurred.
 */
LINKAGE int
sleep_main(int argc,
           char *argv[]){
  int exit_status;
  unsigned long sleep_sec_ul;
  unsigned sleep_sec;
  char *ep;

  exit_status = EXIT_SUCCESS;
  if(argc != 2){
    warnx("must provide one time operand");
    exit_status = EXIT_FAILURE;
  }
  else{
    sleep_sec_ul = strtoul(argv[1], &ep, 10);
    if(argv[1][0] == '\0' || *ep != '\0'){
      warnx("time operand invalid: %s", ep);
      exit_status = EXIT_FAILURE;
    }
    else if(errno == ERANGE && sleep_sec_ul == ULONG_MAX){
      warnx("time operand out of range: %s", argv[1]);
      exit_status = EXIT_FAILURE;
    }
    else{
      while(sleep_sec_ul){
        if(sleep_sec_ul > UINT_MAX){
          sleep_sec = UINT_MAX;
        }
        else{
          sleep_sec = (unsigned)sleep_sec_ul;
        }
        sleep(sleep_sec);
        sleep_sec_ul -= sleep_sec;
      }
    }
  }
  return exit_status;
}

#ifndef TEST
/**
 * Main program entry point.
 *
 * @param[in]     argc See @ref sleep_main.
 * @param[in,out] argv See @ref sleep_main.
 * @return             See @ref sleep_main.
 */
int
main(int argc,
     char *argv[]){
  return sleep_main(argc, argv);
}
#endif /* TEST */

