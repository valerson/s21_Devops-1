# !/bin/bash

echo "script install_all is RUNNING"

# все обновляем, все устанавливаем
apt update
apt-get install -y gcc spawn-fcgi libfcgi-dev 
chmod +x /etc/nginx/start.sh

echo "script install_all is COMPLETED"

