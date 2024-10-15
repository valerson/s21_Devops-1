# !/bin/bash

echo "script install_all is RUNNING"

# все обновляем, все устанавливаем
apt update
apt-get install -y gcc spawn-fcgi libfcgi-dev 
chmod +x /etc/nginx/start.sh

chmod u-s /usr/bin/newgrp /usr/bin/chsh /usr/bin/gpasswd /usr/bin/passwd /usr/bin/su usr/bin/umount usr/bin/chfn usr/bin/mount
chmod g-s /usr/bin/chage /usr/sbin/unix_chkpwd usr/bin/expiry

echo "script install_all is COMPLETED"

