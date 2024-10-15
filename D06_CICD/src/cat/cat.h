#include <stdio.h>
#include <string.h>

struct Flag {
  int b;
  int e;
  int v;
  int n;
  int s;
  int t;
  int read;
};

// void args_print(int argc, char *argv[]);
int args_check_and_parsing(int argc, char *argv[], char *file_name[],
                           int *count_file, struct Flag *fl);

void applying_flags(struct Flag *fl, char *filename[], int count_file);
