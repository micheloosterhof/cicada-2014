#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
int main(int argc, char* argv[]) {

    ssize_t i;
    struct stat st1, st2, sto;
    int fd1, fd2, fdo;

    if (argc != 4) {printf("Usage: %s <input1> <input2> <output>\n", argv[0]); exit(1);}

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {perror("Error opening file for writing"); exit(2);}

    fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {perror("Error opening file for writing"); exit(2);}

    fdo = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR );
    if (fdo == -1) {perror("Error opening file for writing"); exit(2);}

    if (fstat(fd1, &st1) == -1) {perror("Can't determine file1 size"); exit(3);}
    if (fstat(fd2, &st2) == -1) {perror("Can't determine file2 size"); exit(3);}
    // size1==size2 or exit
    if (fstat(fdo, &sto) == -1) {perror("Can't determine fileo size"); exit(3);}

    char* file1 = mmap(NULL, st1.st_size, PROT_READ, MAP_SHARED, fd1, 0);
    if (file1 == MAP_FAILED) {
        perror("Can't map file");
        exit(4);
    }

    char* file2 = mmap(NULL, st2.st_size, PROT_READ, MAP_SHARED, fd2, 0);
    if (file2 == MAP_FAILED) {
        perror("Can't map file");
        exit(4);
    }

/*
    char* fileo = mmap(NULL, st1.st_size, PROT_WRITE, MAP_SHARED, fdo, 0);
    if (fileo == MAP_FAILED) {
        perror("Can't map output file");
        exit(4);
    }
*/

    for (i = 0;i < st1.st_size;i++) {
        char xor[2];
        /* Binary operation goes here.
        If speed is an issue, you may want to do it on a 32 or 64 bit value at
        once, and handle any remaining bytes in special code. */
        //fileo[i] = file1[i] ^ file2[i];
        xor[0] = file1[i] ^ file2[i] ;
        xor[1] = 0;
      
        if ( write( fdo, xor, 1 ) == -1 ) {
		perror( "write error");
		exit(5);
	}
    }

    munmap(file1, st1.st_size);
    munmap(file2, st2.st_size);
 //   munmap(fileo, sto.st_size);
    close(fd1);
    close(fd2);
    close(fdo);
    return 0;
}
