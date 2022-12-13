#include "main_utils.h"
#include "crop.h"
#include "subroutine.h"
#include "td.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  /* Define subcommands */
  const struct subroutine cmds[] = { { "crop", crop_print_help, crop_callback },
                                     { "td", td_print_help, td_callback } };

  const int n_commands = sizeof(cmds) / sizeof(struct subroutine);

  /* Process subcommand */
  for (i = 0; i < n_commands; i++) {
    if (0 == strcmp(cmds[i].command, argv[1])) {
      if ((0 == strcmp("-h", argv[2])) || (0 == strcmp("--help", argv[2]))) {
        (*cmds[0].print_help)();
      }
      (*cmds[0].callback)(argc, argv);
    }
  }

  /* Command not recognized*/
  fprintf(stderr, "Command \"%s\" not recognized.\n\n", argv[1]);
  print_main_help();
  return EXIT_FAILURE;
}
