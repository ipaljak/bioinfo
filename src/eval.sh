#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied."
    NAME="lambda"
  else
    NAME=$1
fi

echo "Running for example: $NAME"

echo "Compiling readings."
g++ Reading.cpp -o reading

echo "Compiling sparc."
g++ -std=c++11 sparc.cpp -o sparc

echo "#1 Running readings for $NAME"
./reading ../data/"$NAME"_layout.fasta ../data/"$NAME"_mappings.sam ../data/"$NAME"_nas.format

echo "#1 Running sparc."
../cgmemtime/cgmemtime -o ../reports/"$NAME"_mem_sparc ./sparc < ../data/"$NAME"_nas.format > ../data/"$NAME"_final

echo "#1 Running dnadiff"
dnadiff ../data/"$NAME"_reference.fasta ../data/"$NAME"_final

echo "$NAME starting score:"
if [ "$NAME" == "lambda" ]
  then
    echo "--------- 86.16 ---------"
  else
    echo "--------- 88.57 ---------"
fi

echo "Our score after 1. iteration:"
cat out.report | grep AvgId | tr -s ' ' | cut -d' ' -f2 | head -1

#echo "#### Running 2. iteration"

# TODO: maybe run mappings again? yes
#echo "Generating mappings from reads (.sam)"
#../graphmap/bin/Linux-x64/graphmap align -r ../data/"$NAME"_final -d ../data/"$NAME"_reads.fastq -o ../data/"$NAME"_mappings2.sam

#echo "#2 Running readings for $NAME"
#./reading ../data/"$NAME"_final ../data/"$NAME"_mappings.sam ../data/"$NAME"_nas.format2

#echo "#2 Running sparc."
#./sparc < ../data/"$NAME"_nas.format2 > ../data/"$NAME"_final2

#echo "#2 Running dnadiff"
#dnadiff ../data/"$NAME"_reference.fasta ../data/"$NAME"_final2

#echo "Our score after 2. iteration:"
#cat out.report | grep AvgId | tr -s ' ' | cut -d' ' -f2 | head -1

