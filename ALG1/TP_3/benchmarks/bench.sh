#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "usage: bash benchmark.sh [BENCHDIR] [executable]"
  exit 2
fi

if [ ! -x $1 ]; then
  echo "invalid executable $1"
  exit 2
fi

benchdir=$1
exe=$2

result="result.txt"
numtests=20
TESTDIR="LOGTIME"

if [ ! -d LOGTIME ]; then
  mkdir LOGTIME
else
  rm -r LOGTIME
  mkdir LOGTIME
fi

if [ -f $timelog ]; then
  rm $timelog 
fi

if [ -f $result ]; then
  rm $result
fi

for filename in $benchdir/*.txt; do
  file=$(basename $filename)
	file=$TESTDIR/"time"${timelog}_${file%.*}.csv
  for i in $(eval echo "{1..$numtests}"); do
    echo "tp3 $filename" >> $result
    ts=$(date +%s%N)
    echo "$($exe $filename)" >> $result
    elapsed=$((($(date +%s%N) - $ts) / 1000))
    
    if (($i != $numtests)); then
      echo "$elapsed," >>$file
    else
      echo "$elapsed" >>$file
    fi
  done
done
