#!/bin/sh.

CUT_FLAG_ONE="-d"
CUT_FLAG_TWO="-f"

CUT_FLAG_TWO_VAL='3'

CSV_FILE_PATH="../ex02/"
CSV_FILE="hh_sorted.csv"

TAIL_FLAG="-n"
TAIL_FLAG_VAL="+2"

AWK_FLAG="-F"
AWK_FLAG_VAL=','

TEMP_FILE_ONE="tmp_one.csv"
TEMP_FILE_TWO="tmp_two.csv"

RES_FILE="hh_positions.csv"

cut $CUT_FLAG_ONE $AWK_FLAG_VAL $CUT_FLAG_TWO $CUT_FLAG_TWO_VAL $CSV_FILE_PATH$CSV_FILE |
tail $TAIL_FLAG $TAIL_FLAG_VAL |
awk $AWK_FLAG $AWK_FLAG_VAL 'BEGIN { OFS="," }
{
    if ($1 ~ /Junior/ && $1 ~ /Middle/ && $1 ~ /Senior/) {
        status="\"Junior/Middle/Senior\"";
    }
    else if ($1 ~ /Junior/ && $1 ~ /Middle/) {
        status="\"Junior/Middle\"";
    }
    else if ($1 ~ /Junior/ && $1 ~ /Senior/) {
        status="\"Junior/Senior\"";
    }
    else if ($1 ~ /Middle/ && $1 ~ /Senior/) {
        status="\"Middle/Senior\"";
    }
    else if ($1 ~ /Junior/) {
        status="\"Junior\"";
    }
    else if ($1 ~ /Middle/) {
        status="\"Middle\"";
    }
    else if ($1 ~ /Senior/) {
        status="\"Senior\"";
    }
    else {
        status="\"-\"";
    }

    print status;
}' > $TEMP_FILE_ONE

awk $AWK_FLAG $AWK_FLAG_VAL 'BEGIN { OFS="," }
NR==FNR { data[NR] = $0; next; }
NR == 1 { print; next; } 
{
    $3 = data[FNR-1];
    print;
}' $TEMP_FILE_ONE $CSV_FILE_PATH$CSV_FILE > $RES_FILE

tail $TAIL_FLAG $TAIL_FLAG_VAL $RES_FILE > $TEMP_FILE_TWO &&
(echo "id","created_at","name","has_test","alternate_url"; cat $TEMP_FILE_TWO;) > $RES_FILE &&
rm $TEMP_FILE_ONE $TEMP_FILE_TWO && clear
