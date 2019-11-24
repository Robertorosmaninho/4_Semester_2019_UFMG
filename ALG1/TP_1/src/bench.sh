mkdir -p results

for i in 10 20 30 40 50 60 70 80 90 100; do
  echo "Vertices: $i - Instruction: $1"
  echo "Input inputs/$1/in_$1_$i.txt"

  for j in 1 2 3 4 5 6 7 8 9 10; do
    # date +%s%N returns the number of seconds since the epoch + current nanoseconds.
    start=$(date +%s%N)
    ./tp1 inputs/$1/in_$1_$i.txt

    elapsed=$((($(date +%s%N) - $start) / 1000)) # time in microseconds

    mv out.txt out_${1}_${i}.txt
    mv out_${1}_${i}.txt results/
    echo "$elapsed" >> results/time__${1}_${i}.txt
  done

done
