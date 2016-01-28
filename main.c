static char const cvsid[] = "$Id: main.c,v 2.1 2005/06/14 22:16:47 jls Exp $";

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>
#include <stdlib.h>


void subr (int64_t I0[], int64_t Out[], int num, int64_t *time, int mapnum);


int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num;
    int64_t *A, *B;
    int64_t tm;
    int mapnum = 0;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
        }

    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
        }

    if (argc < 2) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if (sscanf (argv[1], "%d", &num) < 1) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if ((num < 1) || (num > 1024)) {
        fprintf (stderr, "number of elements must be in the range 1 through 1024\n");
	exit (1);
	}

    A = (int64_t*) Cache_Aligned_Allocate (8 * num * sizeof (int64_t));
    B = (int64_t*) Cache_Aligned_Allocate (num * sizeof (int64_t));

    srandom (99);

    for (i=0; i<8*num; i++) {
        A[i] = random () & 0xff;
	}

    map_allocate (1);

    subr (A, B, num, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    for (i=0; i<num; i++) {
	int t0, t1, t2, t3, t4, t5, t6, t7;
	t0 = A[i];
	t1 = A[num+i];
	t2 = A[2*num+i];
	t3 = A[3*num+i];
	t4 = A[4*num+i];
	t5 = A[5*num+i];
	t6 = A[6*num+i];
	t7 = A[7*num+i];
        fprintf (res_map, "%lld\n", B[i]);
        fprintf (res_cpu, "%d\n", (t0 + t1 - t2) * (t3 * t4 + t5) - (t6 & t7));
	}

    map_free (1);

    exit(0);
    }
