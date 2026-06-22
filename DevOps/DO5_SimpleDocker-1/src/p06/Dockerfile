FROM nginx
WORKDIR /home/
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./hello.c .
COPY ./helper.sh .
RUN apt-get update && apt-get install -y libfcgi-dev gcc spawn-fcgi && rm -rf /var/lib/apt/lists/*
RUN chown -R nginx:nginx /var/cache/nginx
RUN touch /var/run/nginx.pid
RUN chown -R nginx:nginx /var/run/nginx.pid
RUN chmod u-s,g-s /usr/bin/mount /usr/bin/su /usr/bin/chage /usr/bin/gpasswd
RUN chmod u-s,g-s /usr/bin/ /usr/bin/passwd /usr/bin/chfn /usr/bin/umount
RUN chmod u-s,g-s /usr/bin/newgrp /usr/bin/chsh /usr/sbin/unix_chkpwd
USER nginx
ENTRYPOINT ["sh", "./helper.sh"]
HEALTHCHECK NONE