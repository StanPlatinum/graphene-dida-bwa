cp ./mrg.manifest.template /mnt/graphene-dida-bwa/pr/out/
cp ./mrg.cpp /mnt/graphene-dida-bwa/pr/out/
cp ./Makefile /mnt/graphene-dida-bwa/pr/out/
cd /mnt/graphene-dida-bwa/pr/out/
make clean && make SGX=1 run
