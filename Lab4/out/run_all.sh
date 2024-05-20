#!/bin/bash

# parameters=("cycle" "steepest" "candidates" "cache")
parameters=("ils2-1" "ils2-2")
dataSets=("kroA" "kroB")

for parameter in ${parameters[@]}; do
    for dataSet in ${dataSets[@]}; do
        for ((i=0; i<=9; i++)) do
            echo "Running $i $dataSet $parameter"
            ./main $i $dataSet $parameter
        done
    done
done
