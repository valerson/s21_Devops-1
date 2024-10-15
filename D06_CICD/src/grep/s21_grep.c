
/*
1. бахай make
2. запуск - исполняемый файл - флаг с минусом - директори|имя файла|*.расширения
*/

#include "grep.h"

int main(int argc, char *argv[]) {
  char options[2048] = "";
  char *file_name[2048] = {0};
  struct Flag fl = {0};

  int count_file = 0;     // количество файлов
  int count_options = 0;  // количество опций

  args_parsing(argc, argv, options, file_name, &count_file, &count_options,
               &fl);
  grep_function(options, file_name, count_options, count_file, fl);

  return 0;
}
