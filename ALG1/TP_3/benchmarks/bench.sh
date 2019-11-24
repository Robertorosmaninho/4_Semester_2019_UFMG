#!/bin/bash
exe=$(find .. -type f -name "tp3")
for filename in $(pwd)/*.txt; do
  echo "tp3 $filename"
   $exe $filename
done
