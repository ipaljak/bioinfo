#!/bin/bash
# 
# Script that runs everything from scratch
#


echo "Generating mappings from reads (.sam)"
# align
#./graphmap/bin/Linux-x64/graphmap align -r data/lambda_layout.fasta -d data/lambda_reads.fastq -o data/lambda_mappings.sam

./graphmap/bin/Linux-x64/graphmap align -r data/ecoli_layout.fasta -d data/ecoli_reads.fastq -o data/ecoli_mappings.sam

#./src/reading ../data/lambda_layout.fasta ../data/lambda_mappings.sam ../data/nas.format2

#./src/reading ../data/ecoli_layout.fasta ../data/ecoli_mappings.sam ../data/ecoli_nas.format

#./src/sparc < data/ecoli_nas.format > data/ecoli_final

