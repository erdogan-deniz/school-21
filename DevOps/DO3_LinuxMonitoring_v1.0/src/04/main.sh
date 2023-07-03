#!/bin/bash

source colors.cfg

HOSTNAME="$(hostname)" 
TIMEZONE="$(cat /etc/timezone) $(date -u "+%Z") $(date "+%z")" 
USER="$(whoami)" 
OS="$(uname)" 
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

function fon_1 {
    if [[ $column1_background == *[1]* ]] 
    then
        var1="\033[107m"
    elif [[ $column1_background == *[2]* ]] 
    then
        var1="\033[41m"
    elif [[ $column1_background == *[3]* ]] 
    then
        var1="\033[42m"
    elif [[ $column1_background == *[4]* ]] 
    then
        var1="\033[44m"
    elif [[ $column1_background == *[5]* ]] 
    then
        var1="\033[45m"
    elif [[ $column1_background == *[6]* ]] 
    then
        var1="\033[40m"
    fi
    echo $var1
}

function text_1 {
    if [[ $column1_font_color == *[1]* ]] 
    then
        var2="\033[97m"
    elif [[ $column1_font_color == *[2]* ]] 
    then
        var2="\033[31m"
    elif [[ $column1_font_color == *[3]* ]]
    then
        var2="\033[32m"
    elif [[ $column1_font_color == *[4]* ]]
    then
        var2="\033[34m"
    elif [[ $column1_font_color == *[5]* ]]
    then
        var2="\033[35m"
    elif [[ $column1_font_color == *[6]* ]]
    then
        var2="\033[30m"
    fi
    echo $var2
}

function fon_2 {
    if [[ $column2_background == *[1]* ]] 
    then
        var3="\033[107m"
    elif [[ $column2_background == *[2]* ]] 
    then
        var3="\033[41m"
    elif [[ $column2_background == *[3]* ]] 
    then
        var3="\033[42m"
    elif [[ $column2_background == *[4]* ]] 
    then
        var3="\033[44m"
    elif [[ $column2_background == *[5]* ]] 
    then
        var3="\033[45m"
    elif [[ $column2_background == *[6]* ]] 
    then
        var3="\033[40m"
    fi
    echo $var3
}

function text_2 {
    if [[ $column2_font_color == *[1]* ]] 
    then
        var4="\033[97m"
    elif [[ $column2_font_color == *[2]* ]] 
    then
        var4="\033[31m"
    elif [[ $column2_font_color == *[3]* ]]
    then
        var4="\033[32m"
    elif [[ $column2_font_color == *[4]* ]]
    then
        var4="\033[34m"
    elif [[ $column2_font_color == *[5]* ]]
    then
        var4="\033[35m"
    elif [[ $column2_font_color == *[6]* ]]
    then
        var4="\033[30m"
    fi
    echo $var4
}


    fon_1=$(fon_1)
    text_2=$(text_1)
    fon_3=$(fon_2)
    text_4=$(text_2)

COLOR_OFF="\033[0m "


echo -e "${fon_1}${text_2}HOSTNAME = ${fon_3}${text_4}${HOSTNAME}${COLOR_OFF}"
echo -e "${fon_1}${text_2}TIMEZONE= ${fon_3}${text_4}${TIMEZONE}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}USER = ${fon_3}${text_4}${USER}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}OS = ${fon_3}${text_4}${OS}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}DATE = ${fon_3}${text_4}${DATE}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}UPTIME = ${fon_3}${text_4}${UPTIME}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}UPTIME_SEC = ${fon_3}${text_4}${UPTIME_SEC}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}IP = ${fon_3}${text_4}${IP}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}MASK = ${fon_3}${text_4}${MASK}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}GATEWAY = ${fon_3}${text_4}${GATEWAY}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}RAM_TOTAL = ${fon_3}${text_4}${RAM_TOTAL}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}RAM_USED = ${fon_3}${text_4}${RAM_USED}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}RAM_FREE = ${fon_3}${text_4}${RAM_FREE}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}SPACE_ROOT = ${fon_3}${text_4}${SPACE_ROOT}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}SPACE_ROOT_USED = ${fon_3}${text_4}${SPACE_ROOT_USED}${COLOR_OFF}" 
echo -e "${fon_1}${text_2}SPACE_ROOT_FREE = ${fon_3}${text_4}${SPACE_ROOT_FREE}${COLOR_OFF}"
echo
echo "Column 1 background = $column1_background"
echo "Column 1 font color = $column1_font_color"
echo "Column 2 background = $column2_background"
echo "Column 2 font color = $column2_font_color"