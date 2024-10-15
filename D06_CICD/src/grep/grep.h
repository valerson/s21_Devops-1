#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct Flag {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

void args_parsing(int argc, char *argv[], char *options, char *file_name[],
                  int *count_file, int *count_options, struct Flag *fl);

void grep_function(char *options, char *file_name[], int count_options,
                   int count_file, struct Flag fl);

void print_flag_to_print_file(int count_file, int count_res, char *file_name,
                              struct Flag fl);

void print_flag_to_print(int count_file, int count_line, char *temp,
                         char *file_name, char *options, struct Flag fl);
