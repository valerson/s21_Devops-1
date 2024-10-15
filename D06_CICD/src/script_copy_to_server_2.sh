#!/bin/bash

# whoami # определил пользователя - gitlab-runner
# ls

set -e  # Останавливаем выполнение скрипта при любой ошибке

#копируем s21_cat
echo "______COPY s21_cat START______"
scp cat/s21_cat frostdra@10.10.64.2:/usr/local/bin

#копируем s21_grep
echo "______COPY s21_grep START______"
scp grep/s21_grep frostdra@10.10.64.2:/usr/local/bin

#проверяем наличие файлов на сервере 1
if ssh frostdra@10.10.64.2 "[ -f /usr/local/bin/s21_cat ]"; then echo "s21_cat at server 2"; else echo "s21_cat NOT at server 2. FAIL" && exit 1; fi
if ssh frostdra@10.10.64.2 "[ -f /usr/local/bin/s21_grep ]"; then echo "s21_grep at server 2"; else echo "s21_grep NOT at server 2. FAIL" && echo "$CI_JOB_STATUS" && exit 1; fi