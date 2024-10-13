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
    chown 755 /bin/su; \
    chown 755 /usr/bin/chfn; \
    chown 755 /usr/bin/chage; \
    chown 755 /sbin/unix_chkpwd; \
    chown 755 /bin/umount; \
    chown 755 /usr/bin/gpasswd; \
    chown 755 /usr/bin/wall; \
    chown 755 /usr/bin/expiry; \
    chown 755 /usr/bin/newgrp; \
    chown 755 /usr/bin/passwd; \
    chown 755 /bin/mount; \
    chown 755 /usr/bin/chsh; \
    touch /var/run/nginx.pid; \
    chown -R $USERNAME:$USERNAME /var/run/nginx.pid; \
    chown -R $USERNAME:$USERNAME /var/log/nginx; \
    chown -R $USERNAME:$USERNAME /var/cache/nginx

USER $USERNAME
HEALTHCHECK --interval=10s --timeout=30s --start-period=5s --retries=3 CMD curl -sS 127.0.0.1 || exit 1
ENTRYPOINT ["sh", "./run.sh"]