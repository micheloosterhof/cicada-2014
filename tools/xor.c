#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

/*
 * XOR TODO: accept stdin TODO: accept strings on command line TODO: wrap
 * everything but the largest input 
 */

void
usage(char *name)
{
    fprintf(stderr, "%s [-o <outputfile>] <file> <file> [file3]\n", name);
}


int
main(int argc, char *argv[])
{

    ssize_t         i;
    struct stat     st1,
                    st2,
                    st3,
                    sto;
    int             ifiles = 0,
	sources = 0,
	fd1,
	fd2,
	fd3,
	fdo;

    int             c,
                    index;
    char           *outputfile = NULL;
    char           *file1,
                   *file2,
                   *file3;

    while ((c = getopt(argc, argv, "o:")) != -1)
	switch (c) {
	case 'o':
	    outputfile = optarg;
	    break;
	case '?':
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

    sources = ifiles;

    if (sources != 2 && sources != 3) {
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

    fd1 = open(argv[optind], O_RDONLY);
    fprintf(stderr, "inputfile = %s\n", argv[optind]);
    if (fd1 == -1) {
	perror("Error opening file1 for reading");
	exit(2);
    }
    if (fstat(fd1, &st1) == -1) {
	perror("Can't determine file1 size");
	exit(3);
    }
    file1 = mmap(NULL, st1.st_size, PROT_READ, MAP_SHARED, fd1, 0);
    if (file1 == MAP_FAILED) {
	perror("Can't map file1");
	exit(4);
    }


    fd2 = open(argv[optind + 1], O_RDONLY);
    fprintf(stderr, "inputfile = %s\n", argv[optind + 1]);
    if (fd2 == -1) {
	perror("Error opening file2 for reading");
	exit(2);
    }
    if (fstat(fd2, &st2) == -1) {
	perror("Can't determine file2 size");
	exit(3);
    }
    file2 = mmap(NULL, st2.st_size, PROT_READ, MAP_SHARED, fd2, 0);
    if (file2 == MAP_FAILED) {
	perror("Can't map file2");
	exit(4);
    }



    if (ifiles > 2) {
	fd3 = open(argv[optind + 2], O_RDONLY);
	fprintf(stderr, "inputfile = %s\n", argv[optind + 2]);
	if (fd3 == -1) {
	    perror("Error opening file3 for reading");
	    exit(2);
	}
	if (fstat(fd3, &st3) == -1) {
	    perror("Can't determine file3 size");
	    exit(3);
	}
	file3 = mmap(NULL, st3.st_size, PROT_READ, MAP_SHARED, fd3, 0);
	if (file3 == MAP_FAILED) {
	    perror("Can't map file3");
	    exit(4);
	}
    }
    // size1==size2 or exit
    if (fstat(fdo, &sto) == -1) {
	perror("Can't determine fileo size");
	exit(3);
    }

    for (i = 0; i < st1.st_size; i++) {
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

    munmap(file1, st1.st_size);
    close(fd1);

    munmap(file2, st2.st_size);
    close(fd2);

    if (ifiles > 2) {
	munmap(file3, st3.st_size);
	close(fd3);
    }
    // munmap(fileo, sto.st_size);
    close(fdo);
    return 0;
}
