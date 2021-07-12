#!/bin/bash
PARTITIONS=10
rm -f ./output.txt
for i in {2..10}
do
graphene-sgx ./dsp -b25 -p ${PARTITIONS} -g /usr/local/src/work/ref_${PARTITIONS} -u /usr/local/src/work/up -d /usr/local/src/work/pr -e 1 /usr/local/src/work/SRR062634.filt.fastq -r $i >> output.txt;
done
cat output.txt | grep "Running time"
