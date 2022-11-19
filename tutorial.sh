#!/bin/bash

#Required files
REF=<ref.fa>
PAN=<pan.vcf>
READS=<reads.fa>

#Create spaced seed with weight 31 and length 51
echo "111011100101010011010011111110010110010101001110111" > mask.txt

#Build variant graph from pangenome
PanGenie-graph -r $REF -v $PAN -k 51 -o k51

#Count spaced seed k-mers in variant graph
maskjelly -i k51_path_segments.fasta -m mask.txt -f | \
jellyfish count -m 31 -s 3G -p 126 -c 7 -C -L 1 /dev/stdin \
-o masked_genome.jf

#Count spaced seed k-mers in reads 
#(--if: count only k-mers that are also in pangenome graph)
jellyfish dump masked_genome.jf > masked_genome.fa
maskjelly -i $READS -m mask.txt -f | \
jellyfish count -m 31 -s 3G -p 126 -c 7 -C -L 1 \
--if masked_genome.fa /dev/stdin -o masked_reads.jf

#Genotype
MaskedPangenie -i masked_reads.jf -f masked_genome.jf -r $REF -v $PAN -m mask.txt