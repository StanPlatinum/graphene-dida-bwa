#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 512

int main(void){
	
    FILE *fpread = fopen("/mnt/graphene-dida-bwa/pr/out/aln.sam", "r");
	if(fpread == NULL) {
		printf("Encrypted file not found\n");
		return -2;
	}
	//fseek
	fseek(fpread, 0, SEEK_SET);
	//fread
	char b[BUFFER_SIZE] = {0};
	fread(b, BUFFER_SIZE, 1, fpread);
	fclose(fpread);

	printf("b[] = %s\n", b);
	
	return 0;
}