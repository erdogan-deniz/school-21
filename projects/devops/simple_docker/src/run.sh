#!/bin/bash
service nginx start
nginx -s reload
gcc main.c -lfcgi -o main
spawn-fcgi -p 8080 ./main

while true; do
        wait
done