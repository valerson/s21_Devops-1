#!/bin/bash

echo "script start is RUNNING"

# Компиляция и запуск мини-сервера
gcc /etc/nginx/mini_server_c.c -lfcgi -o /etc/nginx/a.out
chmod +x /etc/nginx/a.out

# Запуск FastCGI сервера
spawn-fcgi -p 8080 /etc/nginx/a.out

# Запуск nginx
service nginx start

echo "script start is COMPLETED"

# Поддержание работы контейнера
tail -f /dev/null