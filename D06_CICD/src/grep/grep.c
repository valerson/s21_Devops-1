#include "grep.h"

void args_parsing(int argc, char *argv[], char *options, char *file_name[],
                  int *count_file, int *count_options, struct Flag *fl) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'e') {
        // если е то первая буква флаг, а остальное опция
        fl->e = 1;
        if (strlen(argv[i]) > 2) {
          char *p = argv[i];
          p += 2;
          // Сохраняем аргумент опции
          if (*count_options == 0)
            strcat(options, p);
          else {
            strcat(options, "|");
            strcat(options, p);
          }
          *count_options += 1;
        }
      } else {
        int j = 1;
        while (argv[i][j]) {
          switch (argv[i][j]) {
            case 'f':
              fl->f = 1;
              break;
            case 'v':
              fl->v = 1;
              break;
            case 'i':
              fl->i = 1;
              break;
            case 'c':
              fl->c = 1;
              break;
            case 'l':
              fl->l = 1;
              break;
            case 'n':
              fl->n = 1;
              break;
            case 'h':
              fl->h = 1;
              break;
            case 's':
              fl->s = 1;
              break;
            case 'o':
              fl->o = 1;
              break;
            default:
              break;
          }
          j++;
        }

        if (fl->f) {
          char file_name_flag_f[255];
          char temp[2048];
          i++;
          strcpy(file_name_flag_f, argv[i]);

          FILE *file = fopen(file_name_flag_f, "r");
          if (file == NULL && fl->s == 0) {
            // printf("grep: %s: No such file or directory\n",
            //        file_name_flag_f);
            return;
          }
          while (fgets(temp, 2048, file) != NULL) {
            if (temp[strlen(temp) - 1] == '\n')
              temp[strlen(temp) - 1] = '\0';  // убираем \n если строк
                                              // несколько в файле

            if (*count_options == 0)
              strcat(options, temp);
            else {
              strcat(options, "|");
              strcat(options, temp);
            }
            *count_options += 1;
          }

          fclose(file);
        }
      }
    } else {
      // файл или опция
      FILE *file_temp;
      if ((file_temp = fopen(argv[i], "r")) != NULL) {
        // если открылся - считаем, что файл или если расширение файла
        // один или три символа
        file_name[*count_file] = argv[i];
        *count_file += 1;
        fclose(file_temp);
      } else if (argv[i][strlen(argv[i]) - 2] == '.' ||
                 argv[i][strlen(argv[i]) - 4] == '.') {
        continue;
      } else {
        // Сохраняем аргумент
        // опции
        if (*count_options == 0) {
          strcat(options, argv[i]);
        } else {
          strcat(options, "|");
          strcat(options, argv[i]);
        }
        *count_options += 1;
      }
    }
  }
}

void grep_function(char *options, char *file_name[], int count_options,
                   int count_file, struct Flag fl) {
  for (int f = 0; f < count_file; f++) {
    FILE *file;
    regex_t reg_options;
    int count_line = 1;  // номер строки для n
    int count_res = 0;   // количество строк для с

    int printf_file = 0;  // команда на печать свед по файлу

    char temp[2048];  // максимальная длина строки 2048 байт

    if (fl.i) {
      regcomp(&reg_options, options,
              REG_EXTENDED | REG_ICASE);  // не учитываем регистр
    } else {
      regcomp(&reg_options, options, REG_EXTENDED);
    }

    // пошли по файлам
    if ((file = fopen(file_name[f], "r")) != NULL) {
      while (fgets(temp, 2048, file) != NULL) {
        // tсли найдено и должно было быть найдено (флаг f 0)
        if (regexec(&reg_options, temp, 0, NULL, 0) == 0 && fl.v == 0) {
          if (fl.c && fl.l)
            count_res = 1;
          else if (fl.c && fl.l == 0)
            count_res++;

          print_flag_to_print(count_file, count_line, temp, file_name[f],
                              options, fl);
          printf_file = 1;
        }
        // если не найдено и должно было быть не найдено (флаг f 1)
        else if (regexec(&reg_options, temp, 0, NULL, 0) != 0 && fl.v) {
          if (fl.c && fl.l)
            count_res = 1;
          else if (fl.c && fl.l == 0)
            count_res++;

          print_flag_to_print(count_file, count_line, temp, file_name[f],
                              options, fl);
          printf_file = 1;
        }
        count_line++;
      }

      if (count_options == 1 && printf_file) {
        print_flag_to_print_file(count_file, count_res, file_name[f], fl);
      }

      fclose(file);
    }

    // тут печать если флаги l c f все вместе, лучше не придумал
    if (count_options > 1 && printf_file) {
      print_flag_to_print_file(count_file, count_res, file_name[f], fl);
    } else {
      if (fl.c && printf_file == 0 && fl.h == 0 && count_file > 1) {
        printf("%s:%d\n", file_name[f], count_res);
      }
      if (fl.c && printf_file == 0 && fl.h && count_file != 1) {
        printf("%d\n", count_res);
      }
      if (fl.c && printf_file == 0 && count_file == 1) {
        printf("%d\n", count_res);
      }
    }
    regfree(&reg_options);
  }
}

void print_flag_to_print_file(int count_file, int count_res, char *file_name,
                              struct Flag fl) {
  if (count_file > 1) {
    if (fl.c && fl.h == 0) printf("%s:%d\n", file_name, count_res);
    if (fl.c && fl.h) {
      printf("%d\n", count_res);
    }
    if (fl.l) {
      printf("%s\n", file_name);
    }
  } else {
    if (fl.c) printf("%d\n", count_res);
    if (fl.l) printf("%s\n", file_name);
  }
}

void print_flag_to_print(int count_file, int count_line, char *temp,
                         char *file_name, char *options, struct Flag fl) {
  if (fl.c == 0 && fl.l == 0) {
    //  файл не один, то печатаем его название
    //   если файл и если есть флаг h, то название файлов не печатаем
    if (count_file > 1 && fl.h == 0) printf("%s:", file_name);
    // если флаг n печататем номер строки
    if (fl.n) printf("%d:", count_line);
    //
    if (fl.o) {
      // печатаем только те опции? которые найдены в тексте
      regex_t reg_options;
      if (fl.i) {
        regcomp(&reg_options, options,
                REG_EXTENDED | REG_ICASE);  // не учитываем регистр
      } else {
        regcomp(&reg_options, options, REG_EXTENDED);
      }
      regmatch_t pmatch[2048];
      char *t = temp;
      for (int i = 0; temp[i] != '\0'; i++) {
        if (regexec(&reg_options, t, 1, pmatch, 0) != 0) {
          break;
        }
        if (fl.n && i >= 1) printf("%d:", count_line);
        printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
               t + pmatch[0].rm_so);
        t += pmatch[0].rm_eo;
      }
      regfree(&reg_options);
    }
    //
    if (fl.o == 0 && fl.v == 0) printf("%s", temp);
    if (fl.v) printf("%s", temp);
    // если строка последняя - \n
    if (temp[strlen(temp)] == '\0' && temp[strlen(temp) - 1] != '\n')
      printf("\n");
    if (feof(stdin)) printf("\n");
  }
}

// printf("FLAGS: \n");
// printf("flag e - %d\n", fl->e);
// printf("flag i - %d\n", fl->i);
// printf("flag v - %d\n", fl->v);
// printf("flag c - %d\n", fl->c);
// printf("flag l - %d\n", fl->l);
// printf("flag n - %d\n", fl->n);
// printf("flag h - %d\n", fl->h);
// printf("flag s - %d\n", fl->s);
// printf("flag f - %d\n", fl->f);
// printf("flag o - %d\n", fl->o);

// printf("OPTIONS: \n");
// for (int i = 0; i < *count_options; i++) {
//     printf("%s\n", options[i]);
// }
// printf("FILE_NAMES: \n");
// for (int i = 0; i < *count_file; i++) {
//     printf("%s\n", file_name[i]);
// }
// printf("******************************************\n");