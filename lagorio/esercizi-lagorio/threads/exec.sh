#!/bin/bash


# Number of times to execute 'a.out'
n=10

# Loop to execute 'a.out' n times
for ((i=1; i<=$n; i++)); do
    ./a.out
done
