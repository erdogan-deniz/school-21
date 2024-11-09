#!/bin/bush 

if [ $# != 4 ]
then
    echo "Введите 4 параметра"
    exit
fi

for value in $@; do
        if [ -z $(echo $value | grep "^[1-6]$") ]; then
            echo "Аргумен: $value не подходит. Только значения от 1-6"
            exit
        fi
    done

if [ $1 -eq $2 ] || [ $3 -eq $4 ]
then
    echo "Цвет текста и цвет фона не должны совпадать"
    exit
fi

HOSTNAME="$(hostname)"
TIMEZONE="$(cat /etc/timezone) $(date -u "+%Z") $(date "+%z")"
USER="$(whoami)"
OS="$(awk '{print($3, $2)}' /etc/issue)"
DATE="$(date +"%d %B %Y %H:%M:%S")"
UPTIME="$(uptime -p)"
UPTIME_SEC="$(awk '{print $1}' /proc/uptime)"
IP="$(hostname -i)"
MASK="$(ifconfig | grep -m1 netmask | awk '{print $4}')" 
GATEWAY="$(ip route | grep default | awk '{print $1}')"
RAM_TOTAL="$(free -m | grep Mem | awk '{printf "%.3f", $2/1024 }')" 
RAM_USED="$(free -m | grep Mem | awk '{printf "%.3f", $3/1024 }')" 
RAM_FREE="$(free -m | grep Mem | awk '{printf "%.3f", $4/1024 }')"
SPACE_ROOT="$(df /root | awk ' /\// {printf "%.2f", $2/1024}')"
SPACE_ROOT_USED="$(df /root | awk ' /\// {printf "%.2f", $3/1024}')"
SPACE_ROOT_FREE="$(df /root | awk ' /\// {printf "%.2f", $4/1024}')"


textcolor(){
    case $1 in
        1) echo "\033[37m";;
        2) echo "\033[31m";;
        3) echo "\033[32m";;
        4) echo "\033[34m";;
        5) echo "\033[35m";;
        6) echo "\033[30m";;
    esac
}

backcolor(){
    case $1 in
        1) echo "\033[47m";;
        2) echo "\033[41m";;
        3) echo "\033[42m";;
        4) echo "\033[44m";;
        5) echo "\033[45m";;
        6) echo "\033[40m";;
    esac
}

COLOR_OFF="\033[0m "
param1=$(backcolor "$1")
param2=$(textcolor "$2")
param3=$(backcolor "$3")
param4=$(textcolor "$4")

echo "${param2}${param1}HOSTNAME =${COLOR_OFF}${param4}${param3}${HOSTNAME}${COLOR_OFF}"
echo "${param2}${param1}TIMEZONE =${COLOR_OFF}${param4}${param3}${TIMEZONE}${COLOR_OFF}"
echo "${param2}${param1}USER =${COLOR_OFF}${param4}${param3}${USER}${COLOR_OFF}"
echo "${param2}${param1}OS =${COLOR_OFF}${param4}${param3}${OS}${COLOR_OFF}"
echo "${param2}${param1}DATE =${COLOR_OFF}${param4}${param3}${DATE}${COLOR_OFF}"
echo "${param2}${param1}UPTIME =${COLOR_OFF}${param4}${param3}${UPTIME}${COLOR_OFF}"
echo "${param2}${param1}UPTIME_SEC =${COLOR_OFF}${param4}${param3}${UPTIME_SEC}${COLOR_OFF}"
echo "${param2}${param1}IP =${COLOR_OFF}${param4}${param3}${IP}${COLOR_OFF}"
echo "${param2}${param1}MASK =${COLOR_OFF}${param4}${param3}${MASK}${COLOR_OFF}"
echo "${param2}${param1}GATEWAY =${COLOR_OFF}${param4}${param3}${GATEWAY}${COLOR_OFF}"
echo "${param2}${param1}RAM_TOTAL =${COLOR_OFF}${param4}${param3}${RAM_TOTAL}${COLOR_OFF}"
echo "${param2}${param1}RAM_USED =${COLOR_OFF}${param4}${param3}${RAM_USED}${COLOR_OFF}"
echo "${param2}${param1}RAM_FREE =${COLOR_OFF}${param4}${param3}${RAM_FREE}${COLOR_OFF}"
echo "${param2}${param1}SPACE_ROOT =${COLOR_OFF}${param4}${param3}${SPACE_ROOT}${COLOR_OFF}"
echo "${param2}${param1}SPACE_ROOT_USED =${COLOR_OFF}${param4}${param3}${SPACE_ROOT_USED}${COLOR_OFF}"
echo "${param2}${param1}SPACE_ROOT_FREE =${COLOR_OFF} ${param4}${param3}${SPACE_ROOT_FREE}${COLOR_OFF}"

#надо запускать через sh