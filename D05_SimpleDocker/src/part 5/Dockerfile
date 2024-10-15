# родительский образ
FROM nginx:latest  


# Создание непривилегированного пользователя и выдача прав на использование директории
RUN useradd -d /etc/nginx/ -m -s /bin/bash dockle && \
    chown -R dockle:dockle /etc/nginx/ && \
    chown -R dockle:dockle /var/cache/nginx && \
    chown -R dockle:dockle /var/run && \
    mkdir -p /home/dockle/ && \
    chown dockle:dockle /home/dockle

#  копируем мини-сервер, скрипт установки все 
COPY mini_server_c.c /etc/nginx/ 
COPY install_all.sh /etc/nginx/
COPY start.sh /etc/nginx/
COPY nginx.conf /etc/nginx/

# Добавляем HEAKTHCHECK CIS-DI-0006
HEALTHCHECK --interval=30s --timeout=2s --start-period=5s --retries=3 CMD curl -f http://localhost:8080 || exit 1

# первый запуск - все обновлем, все устанавливаем
RUN sh /etc/nginx/install_all.sh 

# Переключаемся на пользователя dockle
USER dockle

# каждый запуск - компилируем и запускаем мини сервер
CMD ["sh", "/etc/nginx/start.sh"]

