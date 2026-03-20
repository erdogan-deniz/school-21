#!/bin/bash

SUCCESS=0
FAIL=0

for var in -i -v -c -l -n -h -o
do

  t1="clean Makefile $var"
  leaks -quiet -atExit -- ./s21_grep $t1 >> a.txt
  leak=$(grep -A100000 leaks a.txt)
  if [[ $leak == *"0 leaks for 0 total leaked bytes"*  ]];
    then
      echo "SUCCESS $t1"
      (( SUCCESS++ ))
    else
      echo "FAIL $t1"
      (( FAIL++ ))
  fi
  rm a.txt

done

for var in -i -v -c -l -n -h -o
do
  for var2 in -i -v -c -l -n -h -o
  do    
    if [ $var != $var2 ]
    then

        t1="-e for -e option s21_grep.c Makefile $var $var2"
        leaks -quiet -atExit -- ./s21_grep $t1 >> a.txt
        leak=$(grep -A100000 leaks a.txt)
        if [[ $leak == *"0 leaks for 0 total leaked bytes"*  ]];
            then
            echo "SUCCESS $t1"
            (( SUCCESS++ ))
            else
            echo "FAIL $t1"
            (( FAIL++ ))
        fi
        rm a.txt

    fi
  done
done

for var in -i -v -c -l -n -h -o
do
  for var2 in -i -v -c -l -n -h -o
  do
    for var3 in -i -v -c -l -n -h -o
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
      then

        t1="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
        leaks -quiet -atExit -- ./s21_grep $t1 >> a.txt
        leak=$(grep -A100000 leaks a.txt)
        if [[ $leak == *"0 leaks for 0 total leaked bytes"*  ]];
            then
            echo "SUCCESS $t1"
            (( SUCCESS++ ))
            else
            echo "FAIL $t1"
            (( FAIL++ ))
        fi
        rm a.txt

      fi
    done
  done
done

for var in -i -v -c -l -n -h -o
do
  for var2 in -i -v -c -l -n -h -o
  do
    for var3 in -i -v -c -l -n -h -o
    do
      for var4 in -i -v -c -l -n -h -o
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ] && [ $var != $var3 ] && [ $var != $var4 ]
        then

            t1="-e while -e void s21_grep.c Makefile $var $var2 $var3 $var4 -f pattern.txt"
            leaks -quiet -atExit -- ./s21_grep $t1 >> a.txt
            leak=$(grep -A100000 leaks a.txt)
            if [[ $leak == *"0 leaks for 0 total leaked bytes"*  ]];
                then
                echo "SUCCESS $t1"
                (( SUCCESS++ ))
                else
                echo "FAIL $t1"
                (( FAIL++ ))
            fi
            rm a.txt

        fi
      done
    done
  done
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"