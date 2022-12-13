#ifndef RFT_APP_SUBROUTINE_H
#define RFT_APP_SUBROUTINE_H

struct subroutine
{
  char command[10];
  void (*print_help)();
  void (*callback)(int argc, const char* argv[]);
};

#endif /* RFT_APP_SUBROUTINE_H */
