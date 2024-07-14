#!/bin/bash

for ((i=1; i<=50; i++))
do
    mkdir "folder${i}"
    for ((j=1; j<=100; j++))
    do
        mkdir "folder${i}/subfolder${j}"
        for ((k=1; k<=100; k++))
        do
            touch "folder${i}/subfolder${j}/file${k}.txt"
        done
    done
done
