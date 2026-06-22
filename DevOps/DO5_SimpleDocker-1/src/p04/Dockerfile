FROM nginx
WORKDIR /home/
COPY nginx.conf /etc/nginx/nginx.conf
COPY hello.c .
COPY helper.sh .
RUN apt-get update && apt-get install -y libfcgi-dev gcc spawn-fcgi
ENTRYPOINT ["sh", "./helper.sh"]
