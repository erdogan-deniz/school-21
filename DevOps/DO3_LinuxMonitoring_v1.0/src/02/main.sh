#!/bin/bush 

function a
{
    echo "HOSTNAME = $(hostname)" 
    echo "TIMEZONE = $(cat /etc/timezone) $(date -u "+%Z") $(date "+%z")" 
    echo "USER = $(whoami)" 
    echo "OS = $(awk '{print($3, $2)}' /etc/issue)"
    echo "DATE = $(date +"%d %B %Y %H:%M:%S")" 
    echo "UPTIME = $(uptime -p)" 
    echo "UPTIME_SEC = $(awk '{print $1}' /proc/uptime)"
    echo "IP = $(hostname -i)" 
    echo "MASK = $(ifconfig | grep -m1 netmask | awk '{print $4}')" 
    echo "GATEWAY = $(ip route | grep default | awk '{print $3}')" 
    echo "RAM TOTAL = $(free -m | grep Mem | awk '{printf "%.3f", $2/1024 }')" 
    echo "RAM USED = $(free -m | grep Mem | awk '{printf "%.3f", $3/1024 }')" 
    echo "RAM FREE = $(free -m | grep Mem | awk '{printf "%.3f", $4/1024 }')" 
    echo "SPACE ROOT = $(df /root | awk ' /\// {printf "%.2f", $2/1024}')" 
    echo "SPACE ROOT USED = $(df /root | awk ' /\// {printf "%.2f", $3/1024}')" 
    echo "SPACE ROOT FREE = $(df /root | awk ' /\// {printf "%.2f", $4/1024}')"
}

a
echo; echo "Сохранить данные в файл? Y/N:"
read answer
if [[ "$answer" == 'Y' || "$answer" == 'y' ]]
then
    date=$(date +"%d_%m_%Y_%H_%M_%S")
    file="$date.status"
    a >> $file
    echo "Данные сохранились"
else
    echo "Сохранение отменено"
fi

# надо запускать через bash