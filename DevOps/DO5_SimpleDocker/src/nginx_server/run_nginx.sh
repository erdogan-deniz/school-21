#!/bin/bash
service nginx start
nginx -s reload

while true; do
    wait
done