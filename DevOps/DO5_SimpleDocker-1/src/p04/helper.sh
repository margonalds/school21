#!/bin/bash

gcc -o hello hello.c -lfcgi
spawn-fcgi -p 8080 ./hello
service nginx start
while true; do
    wait
done
/bin/bash