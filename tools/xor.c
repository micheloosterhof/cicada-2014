#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

/*
 * XOR TODO: accept stdin TODO: accept strings on command line TODO: wrap
 * everything but the largest input/stdin
 */

enum type { file, xstdin, byte, string };

struct source {
    enum type sourcetype;
    char *data;
    int fd;
    off_t size;     
    int exhausted;
    struct source *next;
};

struct source *head = NULL;

void
usage(char *name)
{
    fprintf(stderr,
	    "%s [-b <byte>] [-o <outputfile>] <file> <file> [file3]\n",
	    name);
}

int
xmmap(char **map, int *fd, off_t * size, const char *filename)
{
    int             fd1;
    struct stat     st1;

    fd1 = open(filename, O_RDONLY);
    fprintf(stderr, "inputfile = %s\n", filename);
    if (fd1 == -1) {
	perror("Error opening file1 for reading");
	exit(2);
    }
    if (fstat(fd1, &st1) == -1) {
	perror("Can't determine file1 size");
	exit(3);
    }
    *map = mmap(NULL, st1.st_size, PROT_READ, MAP_SHARED, fd1, 0);
    if (map == MAP_FAILED) {
	perror("Can't map file1");
	exit(4);
    }

    *fd = fd1;
    *size = st1.st_size;
    return 0;
}

int
main(int argc, char *argv[])
{

    off_t           i,
                    size1,
                    size2,
                    size3;

    int             ifiles = 0,
		    ibytes = 0,
		    istdin = 0,
			isources = 0;
    int
	fd1,
	fd2,
	fd3,
	fdo;

    int             c,
	byte = 0,
	index;
    char           *outputfile = NULL;
    char           *file1,
                   *file2,
                   *file3;

    while ((c = getopt(argc, argv, "b:o:")) != -1)
	switch (c) {
	case 'b':
	    byte = atoi(optarg);
	    ibytes = 1;
	    break;
	case 'o':
	    outputfile = optarg;
	    break;
	case '?':
	    if (optopt == 'b')
		fprintf(stderr, "Option -%c requires an argument.\n",
			optopt);
	    if (optopt == 'o')
		fprintf(stderr, "Option -%c requires an argument.\n",
			optopt);
	    else if (isprint(optopt))
		fprintf(stderr, "Unknown option `-%c'.\n", optopt);
	    else
		fprintf(stderr, "Unknown option character `\\x%x'.\n",
			optopt);
	    return 1;
	default:
	    abort();
	}

    for (index = optind; index < argc; index++) {
	// fprintf(stderr, "inputfile = %s\n", argv[index]);
	ifiles++;
    }

    isources = ifiles + ibytes + istdin;

    if (isources < 2) {
	usage(argv[0]);
	exit(1);
    }

    if (outputfile == NULL) {
	fprintf(stderr, "output to stdout\n");
	fdo = 1;
    } else {
	fprintf(stderr, "outputfile = %s\n", outputfile);
	fdo =
	    open(outputfile, O_CREAT | O_WRONLY | O_TRUNC,
		 S_IRUSR | S_IWUSR);
	if (fdo == -1) {
	    perror("Error opening file for writing");
	    exit(2);
	}
    }

    if (ifiles > 0) xmmap(&file1, &fd1, &size1, argv[optind]);
    if (ifiles > 1) xmmap(&file2, &fd2, &size2, argv[optind + 1]);
    if (ifiles > 2) xmmap(&file3, &fd3, &size3, argv[optind + 2]);

    if (ifiles=1) largest = 0;
    if (ifiles=1)

    moredata = 1;
    do {

        if (ifiles>0) {
		 ret1 = read( fd1, buf1, 1 );
		 if ( ret1 == 0 ) { // wrap
			lseek( fd1, SEEK_SET, 0  );
		 }
        }

        if (ifiles>1) ret2 = read( fd2, buf2, 1 );
		 ret2 = read( fd2, buf2, 1 );
		 if ( ret2 == 0 ) { // wrap
			lseek( fd2, SEEK_SET, 0  );
		 }


        if (ifiles>2) ret3 = read( fd3, buf3, 1 );
		 ret3 = read( fd3, buf3, 1 );
		 if ( ret3 == 0 ) { // wrap
			lseek( fd3, SEEK_SET, 0  );
		 }

        if (istdin>0) ret4 = read( 0, buf4, 1 );
		 if ( ret4 = 0 ) { // the-end 
			moredata = 0;
		 }


    } while( moredata ) 


    for (i = 0; i < size1; i++) {
	char            xor[2];
	/*
	 * Binary operation goes here. If speed is an issue, you may want
	 * to do it on a 32 or 64 bit value at once, and handle any
	 * remaining bytes in special code. 
	 */
	// fileo[i] = file1[i] ^ file2[i];

	if (ifiles == 2) {
	    xor[0] = file1[i] ^ file2[i];
	} else if (ifiles == 3) {
	    xor[0] = file1[i] ^ file2[i] ^ file3[i];
	} else {
	    perror("beep");
	    exit(5);
	}
	xor[1] = 0;

	if (write(fdo, xor, 1) == -1) {
	    perror("write error");
	    exit(5);
	}
    }

    munmap(file1, size1);
    close(fd1);

    munmap(file2, size2);
    close(fd2);

    if (ifiles > 2) {
	munmap(file3, size3);
	close(fd3);
    }
    close(fdo);
    return 0;
}
