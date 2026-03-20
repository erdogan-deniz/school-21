#!/bin/sh.

AWK_FLAG="-F"
AWK_FLAG_VAL=','

FILE_PATH="../ex03/"
FILE_NAME="hh_positions.csv"

awk $AWK_FLAG $AWK_FLAG_VAL 'NR==1 { header = $0; next } {
    split($2, dateParts, "T");
    date = dateParts[1];
    
    if (!(date in seen))
    {
        print header > date".csv";
        seen[date] = 1
    }
    
    print >> date".csv"
}' $FILE_PATH$FILE_NAME && clear
