#!/bin/bash

. script.sh

start_time=$(date +%s.%N)

if [[ $# == 1 && -d $1 && "$1" =~ '/'$ ]]
then
	print_chislo_papok
    print_top5
    print_all
    print_conf
    print_isp_top10
    print_big_top10
	end_time=$(date +%s.%N)
	echo "- Время выполнения скрипта (в секундах) = " `echo "$end_time $start_time" | awk '{printf "%.1lf", $1-$2}'`
else
	echo "Некорректный ввод"
fi