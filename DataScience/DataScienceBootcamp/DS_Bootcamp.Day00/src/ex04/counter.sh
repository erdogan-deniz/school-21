#!/bin/sh.

HEADER="\"name\"","\"count\""

RES_FILE="hh_uniq_positions.csv"

TAIL_FLAG="-n"
TAIL_FLAG_VAL="+2"

GREP_FLAG="-v"
GREP_FLAG_VAL=\"-\"

FILE_PATH="../ex03/"
FILE_NAME="hh_positions.csv"

CUT_FLAG_ONE="-d"
CUT_FLAG_TWO="-f"

CUT_FLAG_ONE_VAL=','
CUT_FLAG_TWO_VAL='3'

UNIQ_FLAG="-c"

SORT_FLAG_ONE="-t"
SORT_FLAG_TWO=-k

SORT_FLAG_TWO_VAL="2,2nr"

echo $HEADER > $RES_FILE

tail $TAIL_FLAG $TAIL_FLAG_VAL $FILE_PATH$FILE_NAME |
grep $GREP_FLAG $GREP_FLAG_VAL |
cut $CUT_FLAG_ONE $CUT_FLAG_ONE_VAL $CUT_FLAG_TWO $CUT_FLAG_TWO_VAL |
sort |
uniq $UNIQ_FLAG |
awk '{ print $2 "," $1 }' |
sort $SORT_FLAG_ONE $CUT_FLAG_ONE_VAL $SORT_FLAG_TWO $SORT_FLAG_TWO_VAL >> $RES_FILE && clear
