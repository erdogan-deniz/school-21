FROM nginx
WORKDIR /home
ARG USERNAME=nginx
USER root
COPY /server/main.c /home/main.c
COPY /server/nginx.conf /etc/$USERNAME/nginx.conf
COPY run.sh /home/run.sh
RUN apt-get update;\
 	apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    apt-get clean; \
	rm -rf /var/lib/apt/lists/*;
EXPOSE 81/tcp
RUN chmod 777 run.sh; \
    gcc main.c -lfcgi -o main; \
    chmod 777 server; \
    chmod 755 /bin/su; \
    chmod 755 /usr/bin/chfn; \
    chmod 755 /usr/bin/chage; \
    chmod 755 /sbin/unix_chkpwd; \
    chmod 755 /bin/umount; \
    chmod 755 /usr/bin/gpasswd; \
    chmod 755 /usr/bin/wall; \
    chmod 755 /usr/bin/expiry; \
    chmod 755 /usr/bin/newgrp; \
    chmod 755 /usr/bin/passwd; \
    chmod 755 /bin/mount; \
    chmod 755 /usr/bin/chsh; \
    touch /var/run/nginx.pid; \
    chown -R $USERNAME:$USERNAME /var/run/nginx.pid; \
    chown -R $USERNAME:$USERNAME /var/log/nginx; \
    chown -R $USERNAME:$USERNAME /var/cache/nginx

USER $USERNAME
HEALTHCHECK --interval=10s --timeout=30s --start-period=5s --retries=3 CMD curl -sS 127.0.0.1 || exit 1
ENTRYPOINT ["sh", "./run.sh"]