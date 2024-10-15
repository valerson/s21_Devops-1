# родительский образ
FROM nginx:latest  

#  копируем мини-сервер, скрипт установки все 

COPY mini_server_c.c /etc/nginx/ 
COPY install_all.sh /etc/nginx/
COPY start.sh /etc/nginx/
COPY nginx.conf /etc/nginx/

# первый запуск - все обновлем, все устанавливаем
RUN sh /etc/nginx/install_all.sh 

# каждый запуск - компилируем и запускаем мини сервер
CMD ["sh", "/etc/nginx/start.sh"]

