#!/bin/bash

SUCCESS=0
FAIL=0
RES=""

for var in -i -v -c -l -n -h -o
do

  t1="clean Makefile $var"
  grep $t1 >> a.txt
  ./s21_grep $t1 >> b.txt
  RES="$(diff -s a.txt b.txt)"
  if [ "$RES" == "Files a.txt and b.txt are identical" ]
    then
      echo "SUCCESS $t1"
      (( SUCCESS++ ))
    else
      echo "FAIL $t1"
      (( FAIL++ ))
  fi
  rm a.txt b.txt

done

for var in -i -v -c -l -n -h -o
do
  for var2 in -i -v -c -l -n -h -o
  do    
    if [ $var != $var2 ]
    then

      t1="-e for -e option s21_grep.c Makefile $var $var2"
      grep $t1 >> a.txt
      ./s21_grep $t1 >> b.txt
      RES="$(diff -s a.txt b.txt)"
      if [ "$RES" == "Files a.txt and b.txt are identical" ]
        then
          echo "SUCCESS $t1"
          (( SUCCESS++ ))
        else
          echo "FAIL $t1"
          (( FAIL++ ))
      fi
      rm a.txt b.txt
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
        grep $t1 >> a.txt
        ./s21_grep $t1 >> b.txt
        RES="$(diff -s a.txt b.txt)"
        if [ "$RES" == "Files a.txt and b.txt are identical" ]
          then
            echo "SUCCESS $t1"
            (( SUCCESS++ ))
          else
            echo "FAIL $t1"
            (( FAIL++ ))
        fi
        rm a.txt b.txt

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
          grep $t1 >> a.txt
          ./s21_grep $t1 >> b.txt
          RES="$(diff -s a.txt b.txt)"
          if [ "$RES" == "Files a.txt and b.txt are identical" ]
            then
              echo "SUCCESS $t1"
              (( SUCCESS++ ))
            else
              echo "FAIL $t1"
              (( FAIL++ ))
          fi
          rm a.txt b.txt

        fi
      done
    done
  done
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"