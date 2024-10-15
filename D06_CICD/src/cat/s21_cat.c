/*

1. бахай make
2. используй имя исп файла s21_cat с флагом (-b -e -E -n -s -t -T)и именем
файла.

или просто юзай тесты, автоматический на кучу случаев - sh ./test_func_cat.sh
ручной sh ./manual_test.sh

*/

#include "cat.h"

int main(int argc, char *argv[]) {
  char *file_name[2048] = {0};
  struct Flag fl = {0};
  int count_file = 0;  // количество файлов

  if (args_check_and_parsing(argc, argv, file_name, &count_file, &fl)) {
    applying_flags(&fl, file_name, count_file);
  }

  return 0;
}

// printf("FILE_NAMES: \n");
// for (int i = 0; i < count_file; i++) {
//     printf("%s\n", file_name[i]);
// }
// printf("flag b - %d\n", fl.b);
// printf("flag e - %d\n", fl.e);
// printf("flag v - %d\n", fl.v);
// printf("flag n - %d\n", fl.n);
// printf("flag s - %d\n", fl.s);
// printf("flag t - %d\n", fl.t);
// printf("flag read - %d\n", fl.read);