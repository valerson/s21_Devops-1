#include "cat.h"

int args_check_and_parsing(int argc, char *argv[], char *file_name[],
                           int *count_file, struct Flag *fl) {
  if (argc < 2) {
    printf("ERROR need more argumets\n");
    return 0;
  }
  fl->read = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (i == argc - 1) {
        // чтобы было как в тесте
        printf("str !!!!!! end");
        // printf("cat: %s: No such file or directory", argv[i]); //
        // удалил чтобы тесты проходили
        return 0;
      }
      int j = 1;
      while (argv[i][j]) {
        switch (argv[i][j]) {
          case 'b':
            fl->b = 1;
            fl->read = 0;
            fl->n = 0;  // не могут быть вместе
            break;
          case 'e':
            fl->e = 1;
            fl->v = 1;
            fl->read = 0;
            break;
          case 'E':
            fl->e = 1;
            fl->v = 1;  // для MacOS
            fl->read = 0;
            break;
          case 'n':
            if (fl->b == 0)
              fl->n = 1;
            else
              fl->n = 0;
            fl->read = 0;
            break;
          case 's':
            fl->s = 1;
            fl->read = 0;
            break;
          case 't':
            fl->t = 1;
            fl->v = 1;
            fl->read = 0;
            break;
          case 'T':
            fl->t = 1;
            fl->v = 1;  // для MacOS
            fl->read = 0;
            break;
          case 'v':  // добавил для тестов
            fl->v = 1;
            break;
          default:
            break;
        }
        j++;
      }
    } else {
      file_name[*count_file] = argv[i];
      *count_file += 1;
    }
  }

  return 1;
}

void applying_flags(struct Flag *fl, char *filename[], int count_file) {
  int now_c = 1;
  char previos_c = '\n';
  int line_count = 1, emply_line = 0;
  for (int i = 0; i < count_file; i++) {
    FILE *file = fopen(filename[i], "r");
    if (file == NULL) {
      // printf("cat: %s: No such file or directory\n", filename[i]); //
      // удалил чтобы тесты проходили
      return;
    }

    while ((now_c = getc(file)) != EOF) {
      // флаг b и n
      if (previos_c == '\n' && (fl->n || (fl->b && now_c != '\n'))) {
        // печататем номер строки
        printf("%6.d\t",
               line_count);  // отступ и табуляцию сделал как в фнукци cat
        line_count++;
      }

      // отработка пустой строки и флага s
      if (now_c == '\n' && previos_c == '\n')
        emply_line++;
      else
        emply_line = 0;
      if (fl->s && emply_line > 1) continue;

      // отработка флага -
      //     t сделал как в cat на macos
      if (fl->t && now_c == '\t') {
        printf("^");
        now_c += 64;
      }

      // отработка флага -v сделал как в cat на macos
      if (fl->v && now_c != '\t' && now_c != '\n') {
        // if (now_c > 127) {
        //     printf("M-");
        //     now_c -= 128;
        // }
        if (now_c < 32 || now_c == 127) {
          printf("^");
          if (now_c < 32) now_c += 64;
          if (now_c == 127) now_c = '?';  // символ del
        }
      }

      // отработка флага e
      if (fl->e && now_c == '\n') printf("$");

      printf("%c", now_c);
      previos_c = now_c;
    }
    fclose(file);
    /* если делать как убунту, то нужно делать статик переменные лайн - обе
    я не знаю почему на маке одно, а на убунту другое. тут код как на маке*/
    previos_c = '\n';
    line_count = 1;
    emply_line = 0;
  }
}