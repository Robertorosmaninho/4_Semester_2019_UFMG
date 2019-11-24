#!/bin/bash

benchdir=$1
exe=$2
for filename in $benchdir/*.txt; do
  echo "tp3 $filename"
   $exe $filename
done
