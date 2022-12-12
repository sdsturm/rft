#include "config.h"
#include "touchstone.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct subroutine
{
  char command[10];
  void (*print_help)();
  void (*callback)(int argc, const char* argv[]);
};

void
crop_print_help()
{
  printf("Help page for subroutine crop...\n");
  /* TODO */
  exit(EXIT_SUCCESS);
}

void
crop_callback(int argc, const char* argv[])
{

  /* TODO */
}

struct subroutine cmds[] = { { "crop", crop_print_help, crop_callback } };

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

int
main(int argc, char const* argv[])
{
  int i;

  /* Call without any arguments */
  if (1 == argc) {
    print_main_help();
  }

  /* Options causing message and immediate exit */
  if ((0 == strcmp("-h", argv[1])) || (0 == strcmp("--help", argv[1]))) {
    print_main_help();
  }
  if ((0 == strcmp("-v", argv[1])) || (0 == strcmp("--version", argv[1]))) {
    print_version();
  }

  /* Process subcommand */
  for (i = 0; i < 1; i++) {
    if (0 == strcmp(cmds[i].command, argv[1])) {
      if ((0 == strcmp("-h", argv[2])) || (0 == strcmp("--help", argv[2]))) {
        (*cmds[0].print_help)();
      }
      (*cmds[0].callback)(argc, argv);
    }
  }

  const char* filename = argv[1];

  int n_ports;
  int n_freq;
  double r_ref;
  double* freq;
  rft_complex* data;

  parse_touchstone(filename, &n_ports, &n_freq, &r_ref, &freq, &data);

  return EXIT_SUCCESS;
}
