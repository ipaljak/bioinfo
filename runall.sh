#!/bin/bash
# 
# Script that runs everything from scratch
#

echo "Generating overlaps from reads (MHAP)"

# Overlap all reads from a given FASTA/FASTQ file and report overlaps in MHAP format (fast):  
./graphmap/bin/Linux-x64/graphmap owler -r data/lambda_reads.fastq -d data/lambda_reads.fastq -o data/lambda_overlaps.mhap

