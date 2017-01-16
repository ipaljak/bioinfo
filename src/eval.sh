#!/bin/bash

echo "Compiling."
g++ -std=c++11 sparc.cpp -o sparc

echo "Running sparc."
./sparc < ../data/lambda_nas.format > ../data/lambda_final

echo "Running dnadiff."
dnadiff ../data/lambda_reference.fasta ../data/lambda_final

echo "Echoing score:"
echo "Starting score: 86.16"
cat ../data/out.report | grep AvgId

