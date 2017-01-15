#!/bin/bash
# 
# Script that runs everything from scratch
#

echo "Generating overlaps from reads (MHAP)"

# Overlap all reads from a given FASTA/FASTQ file and report overlaps in MHAP format (fast):  
./graphmap/bin/Linux-x64/graphmap align -r data/lambda_layout.fasta -d data/lambda_reads.fastq -o data/lambda_overlaps.sam

