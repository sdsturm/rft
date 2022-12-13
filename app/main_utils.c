#include "main_utils.h"

#include "../config.h"

#include <stdlib.h>
#include <string.h>

void
print_main_help()
{
  printf("Usage: rft [-v | --version] [-h | --help] <command> [<args>]\n");
  printf("\n");
  printf("Working on Touchstone files\n");
  printf("   crop       Bandpass filter Touchstone file\n");
  printf("   tdr        Compute time-domain from Touchstone file\n");
  exit(EXIT_SUCCESS);
}

void
print_version()
{
  printf("rft version %d.%d (compiled %s)\n",
         RFT_VERSION_MAJOR,
         RFT_VERSION_MINOR,
         __DATE__);
  exit(EXIT_SUCCESS);
}