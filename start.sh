#!/bin/bash

i=$2
di=$3
N=$4
d=$5

while [ $i -le $N ]
do
 ./$1 $i $d
 let i=i+$di
done
