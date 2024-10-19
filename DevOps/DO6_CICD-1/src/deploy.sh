#!/bin/bash

echo "Deploying process..."

scp src/C2_SimpleBashUtils/cat/s21_cat charisel@10.10.0.2:/usr/local/bin/
scp src/C2_SimpleBashUtils/grep/s21_grep charisel@10.10.0.2:/usr/local/bin/

ssh charisel@10.10.0.2 ls /usr/local/bin

echo "Deploying process ends..."